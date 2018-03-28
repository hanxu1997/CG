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
using namespace std;

// ������ɫ��Դ��
const char *vertexShaderSource = "#version 440 core\n"
			"layout (location = 0) in vec3 Position;\n"
			"out vec4 vetexColor;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(Position, 1.0);\n"
			"   vetexColor = vec4(0.38, 0.38, 0.50, 1.0);\n"
			"}\0";
// Ƭ����ɫ��Դ��
const char *fragmentShaderSource = "#version 440 core\n"
								"out vec4 FragColor;\n"
								"in vec4 vetexColor;\n"
								"void main()\n"
								"{\n"
								"   FragColor = vetexColor;\n"
								"}\n\0";

void processInput(GLFWwindow *);
void framebuffer_size_callback(GLFWwindow*, int, int);

int main() {
	// ��ʼ��GLFW
	glfwInit();
	// ����GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// �������ڶ��󣬴�����кʹ�����ص����ݣ�
	// ���һᱻGLFW����������Ƶ�����õ�
	GLFWwindow* window = glfwCreateWindow(1200, 800, "HellloTriangle", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	// ֪ͨGLFW�����Ǵ��ڵ�����������Ϊ��ǰ�̵߳���������
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	// ע���������������GLFW����ϣ��ÿ�����ڵ�����С��ʱ������������
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// GLAD: �����OpenGL����ָ��
	// �����κ�OpenGL����֮ǰ��Ҫ��ʼ��GLAD
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
	// ImGui::StyleColorsDark();
	ImVec4 clear_color = ImVec4(0.92f, 0.92f, 0.92f, 1.0f);

	// ������������ɫ������
	// 1. ������ɫ��
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// ��鶥����ɫ���Ƿ����ɹ�
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}
	// 2. Ƭ����ɫ��
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// ���Ƭ����ɫ���Ƿ����ɹ�
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
	}
	// ������ɫ��
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// ����Ƿ����ӳɹ�
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
	}
	// ������ɺ�ɾ����ɫ������
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	// ������ɫ���������
	glUseProgram(shaderProgram);

	// ���㻺����󣬶����������
	unsigned int VBO;
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// ��
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// ���Ӷ�������
	// λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// ������������
	int point0[] = {-200, -100 };
	int point1[] = {200, -100};
	int point2[] = {0, 200 };
	// Բ�İ뾶
	int r = 100;

	ImGuiWindowFlags window_flags = 0;
	bool show_triangle_window = true;
	bool show_circle_window = false;
	bool show_rasterization_window = false;

	cout << "render loop" << endl;
	// ��Ⱦѭ�� render loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glfwPollEvents();
		ImGui_ImplGlfwGL3_NewFrame();
		// ����ɫ
		glClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		bool* p_open = NULL;
		// ������-----------------------------------------------------------------------------------
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
				ImGui::MenuItem("Circle Window", NULL, &show_circle_window);
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
				}

				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		if (ImGui::CollapsingHeader("Help"))
		{
			ImGui::TextWrapped("Please click 'Windows' to choose different functions. \n\n");
		}
		ImGui::Spacing();
		ImGui::Text("Hello!");
		ImGui::End();
		// �����ڻ������--------------------------------------------------------------------------	
		// rendering lines
		if (show_triangle_window)
		{
			ImGui::Begin("Triangle Window", &show_triangle_window);
			ImGui::InputInt2("point0", point0);
			ImGui::InputInt2("point1", point1);
			ImGui::InputInt2("point2", point2);
			ImGui::SliderInt("x0", &point0[0], -600, 600);
			ImGui::SliderInt("y0", &point0[1], -400, 400);
			ImGui::SliderInt("x1", &point1[0], -600, 600);
			ImGui::SliderInt("y1", &point1[1], -400, 400);
			ImGui::SliderInt("x2", &point2[0], -600, 600);
			ImGui::SliderInt("y2", &point2[1], -400, 400);

			vector<float> p1 = normalize(BresenhamLine(point0[0], point0[1], point2[0], point2[1]), 1200, 800);
			int length1 = p1.size();
			float* line1 = getRealCoordinate(p1, length1);
			vector<float> p2 = normalize(BresenhamLine(point1[0], point1[1], point2[0], point2[1]), 1200, 800);
			int length2 = p2.size();
			float* line2 = getRealCoordinate(p2, length2);
			vector<float> p3 = normalize(BresenhamLine(point0[0], point0[1], point1[0], point1[1]), 1200, 800);
			int length3 = p3.size();
			float* line3 = getRealCoordinate(p3, length3);
			glBufferData(GL_ARRAY_BUFFER, 3 * length1 * sizeof(float), line1, GL_STATIC_DRAW);
			glPointSize(5.0f);
			glDrawArrays(GL_POINTS, 0, length1 / 2);
			glBufferData(GL_ARRAY_BUFFER, 3 * length2 * sizeof(float), line2, GL_STATIC_DRAW);
			glPointSize(5.0f);
			glDrawArrays(GL_POINTS, 0, length2 / 2);
			glBufferData(GL_ARRAY_BUFFER, 3 * length3 * sizeof(float), line3, GL_STATIC_DRAW);
			glPointSize(5.0f);
			glDrawArrays(GL_POINTS, 0, length3 / 2);
			ImGui::End();
			delete[]line1;
			delete[]line2;
			delete[]line3;
		}
		// rendering points
		if (show_circle_window)
		{
			ImGui::Begin("Circle Window", &show_circle_window);
			ImGui::SliderInt("Radius", &r, 0, 400);
			vector<float> circleVector = normalize(BresenhamCircle(0, 0, r), 1200, 800);
			int circleLength = circleVector.size();
			float* circle = getRealCoordinate(circleVector, circleLength);
			glBufferData(GL_ARRAY_BUFFER, 3 * circleLength * sizeof(float), circle, GL_STATIC_DRAW);
			glPointSize(5.0f);
			glDrawArrays(GL_POINTS, 0, circleLength/2);
			ImGui::End();
			delete[] circle;
		}
		if (show_rasterization_window) {
			ImGui::Begin("Rasterization Window", &show_rasterization_window);
			ImGui::InputInt2("point0", point0);
			ImGui::InputInt2("point1", point1);
			ImGui::InputInt2("point2", point2);
			ImGui::SliderInt("x0", &point0[0], -600, 600);
			ImGui::SliderInt("y0", &point0[1], -400, 400);
			ImGui::SliderInt("x1", &point1[0], -600, 600);
			ImGui::SliderInt("y1", &point1[1], -400, 400);
			ImGui::SliderInt("x2", &point2[0], -600, 600);
			ImGui::SliderInt("y2", &point2[1], -400, 400);
			Point v1(point0[0], point0[1]);
			Point v2(point1[0], point1[1]);
			Point v3(point2[0], point2[1]);
			vector<float> c1 = normalize(drawTriangle(v1, v2, v3), 1200, 800);
			int clength = c1.size();
			float* c2 = getRealCoordinate(c1, clength);
			glBufferData(GL_ARRAY_BUFFER, 3 * clength * sizeof(float), c2, GL_STATIC_DRAW);
			glPointSize(5.0f);
			glDrawArrays(GL_POINTS, 0, clength / 2);
			ImGui::End();
			delete[] c2;
		}
		// Rendering
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
	}

	// �ͷ�/ɾ��֮ǰ�����������Դ
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}



// �������
void processInput(GLFWwindow *window)
{
	// glfwGetKey
	// ���룺һ�������Լ�һ������(�������û��Ƿ����˷��ؼ�Esc)
	// ���أ���������Ƿ����ڱ�����
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

// �Դ���ע��һ���ص�������������ÿ�δ��ڴ�С��������ʱ�򱻵���
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// ���ô��ڵ�ά��
	glViewport(0, 0, width, height);
}
