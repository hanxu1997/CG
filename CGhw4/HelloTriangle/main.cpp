#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

// 顶点着色器源码
const char *vertexShaderSource = "#version 440 core\n"
		"layout (location = 0) in vec3 Position;\n"
		"layout (location = 1) in vec3 Color;\n"
		"out vec3 vetexColor;\n"
		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"void main()\n"
		"{\n"
		"   gl_Position =  projection * view * model * vec4(Position, 1.0);\n"
		"   vetexColor = Color;\n"
		"}\0";
// 片段着色器源码
const char *fragmentShaderSource = "#version 440 core\n"
		"out vec4 FragColor;\n"
		"in vec3 vetexColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(vetexColor, 1.0f);\n"
		"}\n\0";

void processInput(GLFWwindow *);
void framebuffer_size_callback(GLFWwindow*, int, int);

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
	// ImGui::StyleColorsDark();
	ImVec4 clear_color = ImVec4(0.92f, 0.92f, 0.92f, 1.0f);

	// 创建并编译着色器程序
	// 1. 顶点着色器
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// 检查顶点着色器是否编译成功
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}
	// 2. 片段着色器
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// 检查片段着色器是否编译成功
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
	}
	// 链接着色器
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// 检查是否链接成功
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
	}
	// 链接完成后删除着色器对象
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	// 激活着色器程序对象
	glUseProgram(shaderProgram);

	// 顶点缓冲对象，顶点数组对象
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// 绑定
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// 链接顶点属性
	// 位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// 颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	// 8个顶点坐标
	float vertices[] = {
		-0.2f,  0.2f,  0.2f,  0.0f, 1.0f, 0.8f,
		0.2f,  0.2f,  0.2f,  0.0f, 1.0f, 1.0f,
		0.2f, -0.2f,  0.2f,  0.0f, 0.8f, 1.0f,
		-0.2f, -0.2f,  0.2f,  0.0f, 0.6f, 1.0f,
		-0.2f,  0.2f,  -0.2f,  0.0f, 0.4f, 1.0f,
		0.2f,  0.2f,  -0.2f,  0.0f, 0.2f, 1.0f,
		0.2f, -0.2f,  -0.2f,  0.0f, 0.0f, 1.0f,
		-0.2f, -0.2f,  -0.2f,  0.0f, 0.0f, 0.8f

	};
	// 索引
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0,
		4, 5, 7,
		5, 6, 7,
		0, 4, 3,
		4, 7, 3,
		1, 5, 2,
		5, 6, 2,
		4, 5, 0, 
		5, 1, 0,
		7, 6, 3,
		6, 2, 3
	};
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	bool depth = true;
	float xDistance = 0.0f;
	bool toRight = true;
	float translateV = 0.02f;
	float scaleSize = 1.0f;
	bool toBigger = true;
	float scaleV = 0.02f;
	ImGuiWindowFlags window_flags = 0;
	bool show_rotation_window = true;
	bool show_translation_window = false;
	bool show_scaling_window = false;
	
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
				ImGui::MenuItem("Rotation Window", NULL, &show_rotation_window);
				if (show_rotation_window == true)
				{
					show_scaling_window = false;
					show_translation_window = false;
				}
				ImGui::MenuItem("Translation Window", NULL, &show_translation_window);
				if (show_translation_window == true)
				{
					show_scaling_window = false;
					show_rotation_window = false;
				}
				ImGui::MenuItem("Scaling Window", NULL, &show_scaling_window);
				if (show_scaling_window == true)
				{
					show_translation_window = false;
					show_rotation_window = false;
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
		// 主窗口绘制完成--------------------------------------------------------------------------	
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		if (show_rotation_window)
		{
			ImGui::Begin("Rotation Window", &show_rotation_window);
			ImGui::Spacing();
			ImGui::Checkbox("Enable", &depth);
			if (depth) {
				// 深度！
				glEnable(GL_DEPTH_TEST);
			}
			else {
				glDisable(GL_DEPTH_TEST);
			}
			// 绕y=z旋转
			model = glm::rotate(model, (GLfloat)glfwGetTime() * 50.0f, glm::vec3(0.0f, 1.0f, 1.0f));
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
			projection = glm::perspective(45.0f, 1.5f, 0.1f, 100.0f);
			GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
			GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
			GLint projLoc = glGetUniformLocation(shaderProgram, "projection");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
			glBindVertexArray(EBO);
			ImGui::End();
		}
	
		if (show_translation_window) {
			ImGui::Begin("Translation Window", &show_translation_window);
			ImGui::Spacing();
			ImGui::SliderFloat("translateV", &translateV, 0.0f, 0.1f);
			if (toRight == true) {
				xDistance += translateV;
				if (xDistance > 0.8f) {
					toRight = false;
				}
			} else {
				xDistance -= translateV;
				if (xDistance < -0.8f) {
					toRight = true;
				}
			}
			model = glm::translate(model, glm::vec3(xDistance, 0.0f, 0.0f));
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
			projection = glm::perspective(45.0f, 1.5f, 0.1f, 100.0f);
			GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
			GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
			GLint projLoc = glGetUniformLocation(shaderProgram, "projection");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
			glBindVertexArray(EBO);
			ImGui::End();
		}

		if (show_scaling_window) {
			ImGui::Begin("Scaling Window", &show_scaling_window);
			ImGui::Spacing();
			ImGui::SliderFloat("scaleV", &scaleV, 0.0f, 0.1f);
			if (toBigger == true) {
				scaleSize += scaleV;
				if (scaleSize > 2.0f) {
					toBigger = false;
				}
			} else {
				scaleSize -= scaleV;
				if (scaleSize < 0.2f) {
					toBigger = true;
				}
			}
			model = glm::scale(model, glm::vec3(scaleSize, scaleSize, scaleSize));
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
			projection = glm::perspective(45.0f, 1.5f, 0.1f, 100.0f);
			GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
			GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
			GLint projLoc = glGetUniformLocation(shaderProgram, "projection");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
			glBindVertexArray(EBO);
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
	glDeleteBuffers(1, &EBO);
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
}

// 对窗口注册一个回调函数，它会在每次窗口大小被调整的时候被调用
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// 设置窗口的维度
	glViewport(0, 0, width, height);
}
