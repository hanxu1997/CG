#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include "draw.h"
#include "shader.h"
#include "Camera.h"
using namespace std;

void processInput(GLFWwindow *);
void framebuffer_size_callback(GLFWwindow*, int, int);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

bool firstMouse = true;
float lastX = 1200.0f / 2.0;
float lastY = 800.0 / 2.0;
GLfloat xpos, ypos;

vector<Point>Points;
int pointNum = 0;
int lineindex = 0;
int lineup = 0;
glm::vec3 curveColor = glm::vec3(0.38, 0.38, 0.50);
bool start = false;


void RenderPoint(Point p) {
	vector<Point> item;
	item.push_back(p);
	float* point = getRealCoordinate(item, 1, 1200, 800);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), point, GL_STATIC_DRAW);
	glPointSize(5.0f);
	glDrawArrays(GL_POINTS, 0, 1);
	delete[] point;
}
void RenderLine(Point p1, Point p2) {
	vector<Point> item;
	item.push_back(p1);
	item.push_back(p2);
	float* line = getRealCoordinate(item, 2, 1200, 800);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), line, GL_STATIC_DRAW);
	glLineWidth(3.0f);
	glDrawArrays(GL_LINES, 0, 2);
	delete[] line;
}
void RenderCurve(vector<Point> p) {
	int length = p.size();
	float* curve = getRealCoordinate(p, length, 1200, 800);
	glBufferData(GL_ARRAY_BUFFER, 6 * length * sizeof(float), curve, GL_STATIC_DRAW);
	glPointSize(5.0f);
	glDrawArrays(GL_POINTS, 0, length);
	delete[] curve;
}



void cursor_position_callback(GLFWwindow* window, double x, double y)
{
	xpos = float((x - 1200 / 2) );
	ypos = float(0 - (y - 800 / 2) );
	return;
}

int main() {
	// 初始化GLFW
	glfwInit();
	// 配置GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 创建窗口对象，存放所有和窗口相关的数据，
	// 而且会被GLFW的其他函数频繁地用到
	GLFWwindow* window = glfwCreateWindow(1200, 800, "HellloTriangle", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	// 通知GLFW将我们窗口的上下文设置为当前线程的主上下文
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	// 注册这个函数，告诉GLFW我们希望每当窗口调整大小的时候调用这个函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	// GLAD: 管理的OpenGL函数指针
	// 调用任何OpenGL函数之前需要初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	// Setup ImGui binding
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfwGL3_Init(window, true);

	// Setup style
	ImVec4 clear_color = ImVec4(0.92f, 0.92f, 0.92f, 1.0f);

	// 创建并编译着色器程序
	int curveShader = shaderprogram(vertexShaderSource, fragmentShaderSource);
	glUseProgram(curveShader);

	// 顶点缓冲对象，顶点数组对象
	unsigned int VBO;
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// 绑定
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 链接顶点属性
	// 位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);



	ImGuiWindowFlags window_flags = 0;
	bool show_triangle_window = true;
	bool show_circle_window = false;
	bool show_rasterization_window = false;

	cout << "render loop" << endl;
	// 渲染循环 render loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glfwPollEvents();
		ImGui_ImplGlfwGL3_NewFrame();
		// 背景色
		glClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		bool* p_open = NULL;
		// 主窗口-----------------------------------------------------------------------------------
		ImGui::Begin("main", p_open, window_flags);
		window_flags |= ImGuiWindowFlags_MenuBar;
		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("Windows"))
			{
				ImGui::MenuItem("Line Window", NULL, &show_triangle_window);
				if (show_triangle_window == true)
				{
					show_rasterization_window = false;
					show_circle_window = false;
				}
			/*	ImGui::MenuItem("Circle Window", NULL, &show_circle_window);
				if (show_circle_window == true)
				{
					show_rasterization_window = false;
					show_triangle_window = false;
				}
				ImGui::MenuItem("Rasterization Window", NULL, &show_rasterization_window);
				if (show_rasterization_window == true)
				{
					show_circle_window = false;
					show_triangle_window = false;
				}*/

				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		/*if (ImGui::CollapsingHeader("Help"))
		{
			ImGui::TextWrapped("Please click 'Windows' to choose different functions. \n\n");
		}*/
		ImGui::Spacing();
		ImGui::Text("Press 'q' to draw points.");
		ImGui::Text("Press 'e' to stop drawing.");
		ImGui::End();
		// 主窗口绘制完成--------------------------------------------------------------------------	
		// rendering lines
		if (show_triangle_window)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			ImGui::Begin("Curve Window", &show_triangle_window);
			// color
			setVec3(curveShader, "color", curveColor);
			ImGui::ColorEdit3("color", (float*)&curveColor);
			// add points
			if (Points.size() < 4 && ImGui::IsMouseClicked(0) && start) {
				Points.push_back(Point(xpos, ypos));
			}
			vector<Point>::const_iterator k = Points.begin();
			// delete points
			if (Points.size() >= 1) {
				ImGui::Text("delete point");
				if (ImGui::Button("1")) {
					Points.erase(k);
				}
			}
			ImGui::SameLine();
			if (Points.size() >= 2) {
				if (ImGui::Button("2")) {
					Points.erase(k+1);
				}
			}
			ImGui::SameLine();
			if (Points.size() >= 3) {
				if (ImGui::Button("3")) {
					Points.erase(k + 2);
				}
			}
			ImGui::SameLine();
			if (Points.size() == 4) {
				if (ImGui::Button("4")) {
					Points.erase(k + 3);
				}
			}

			// Render Points
			for (int i = 0; i < Points.size(); i++) {
				RenderPoint(Points[i]);
			}
			// Render Lines
			lineup = Points.size() - 1;
			for (int j = lineindex; j < lineup; j++) {
				RenderLine(Points[j], Points[j + 1]);
			}
			// Render Curve
			if (Points.size() == 4) {
				ImGui::SliderInt("P1.x", &Points[0].x, -600, 600);
				ImGui::SliderInt("P1.y", &Points[0].y, -400, 400);
				ImGui::SliderInt("P2.x", &Points[1].x, -600, 600);
				ImGui::SliderInt("P2.y", &Points[1].y, -400, 400);
				ImGui::SliderInt("P3.x", &Points[2].x, -600, 600);
				ImGui::SliderInt("P3.y", &Points[2].y, -400, 400);
				ImGui::SliderInt("P4.x", &Points[3].x, -600, 600);
				ImGui::SliderInt("P4.y", &Points[3].y, -400, 400);
				vector<Point> curve = BezierCurve(Points[0], Points[1], Points[2], Points[3]);
				RenderCurve(curve);
			}
			ImGui::End();
		}
		// Rendering
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
	}

	// 释放/删除之前分配的所有资源
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}



// 输入控制
void processInput(GLFWwindow *window)
{
	// glfwGetKey
	// 输入：一个窗口以及一个按键(这里检查用户是否按下了返回键Esc)
	// 返回：这个按键是否正在被按下
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		start = true;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		start = false;
	}
}

// 对窗口注册一个回调函数，它会在每次窗口大小被调整的时候被调用
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// 设置窗口的维度
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	// camera.ProcessMouseMovement(xoffset, yoffset);
}