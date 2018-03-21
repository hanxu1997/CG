#include <glad/glad.h>
#include <GLFW/glfw3.h>
/*GLAD的头文件包含了正确的OpenGL头文件（例如GL/gl.h），
所以需要在其它依赖于OpenGL的头文件之前包含GLAD。*/
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include <stdio.h>
#include <iostream>
using namespace std;

// 顶点着色器源码
const char *vertexShaderSource = "#version 440 core\n"
								"layout (location = 0) in vec3 Position;\n"
								"layout (location = 1) in vec3 Color;\n"
								"out vec3 vetexColor;\n"
								"void main()\n"
								"{\n"
								"   gl_Position = vec4(Position, 1.0);\n"
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
// 输入控制
void processInput(GLFWwindow *);
// 对窗口注册一个回调函数，它会在每次窗口大小被调整的时候被调用
void framebuffer_size_callback(GLFWwindow*, int, int);
int main()
{
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

	// 三角形顶点设置
	float vertices[] = {
		// positions         // colors
		-0.5f, -0.2f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
		0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,    // top 
		0.5f, -0.2f, 0.0f, 0.0f, 0.0f, 1.0f  // bottom right
	};

	float points[] = {
		// positions         // colors
		-0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // left
		0.0f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // mid
		0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f   // right
	};
	float lines[] = {
		// positions         // colors
		-0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // start
		0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // end
	};

	float severalTriangles[] = {
		// first
		0.5f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.2f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		// second
		-0.5f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.2f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f
	};
	unsigned int indices[] = {
		0, 1, 2,
		3, 4, 5
	};

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// 颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// 三角形顶点颜色存储及更新
	float left_color[] = { 1.0, 0.0, 0.0 };
	float top_color[] = { 0.0, 1.0, 0.0 };
	float right_color[] = { 0.0, 0.0, 1.0 };
	
	ImGuiWindowFlags window_flags = 0;
	bool show_triangle_window = true;
	bool show_point_window = false;
	bool show_line_window = false;
	bool show_severaltriangles_window = false;

	//-----------------------------------------------------------------------------------------------------------
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
			ImGui::MenuItem("Triangle Window", NULL, &show_triangle_window);
			if (show_triangle_window == true)
			{
				show_point_window = false;
				show_line_window = false;
				show_severaltriangles_window = false;
			}
			ImGui::MenuItem("Point Window", NULL, &show_point_window);
			if (show_point_window == true)
			{
				show_triangle_window = false;
				show_line_window = false;
				show_severaltriangles_window = false;
			}
			ImGui::MenuItem("line Window", NULL, &show_line_window);
			if (show_line_window == true)
			{
				show_triangle_window = false;
				show_point_window = false;
				show_severaltriangles_window = false;
			}
			ImGui::MenuItem("several triangles Window", NULL, &show_severaltriangles_window);
			if (show_severaltriangles_window == true)
			{
				show_triangle_window = false;
				show_point_window = false;
				show_line_window = false;
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
		// ImGui::Checkbox("Triangle Window", &show_triangle_window);
		ImGui::End();
		// 主窗口绘制完成---------------------------------------------------------------------------
		// rendering Triangle
		if (show_triangle_window)
		{
			ImGui::Begin("Triangle Window", &show_triangle_window);
			ImGui::ColorEdit3("leftPoint", (float*)&left_color);
			ImGui::ColorEdit3("TopPoint", (float*)&top_color);
			ImGui::ColorEdit3("RightPoint", (float*)&right_color);
			// 把三角形顶点数组复制到一个顶点缓冲中，供OpenGL使用
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			vertices[3] = left_color[0];
			vertices[4] = left_color[1];
			vertices[5] = left_color[2];
			vertices[9] = top_color[0];
			vertices[10] = top_color[1];
			vertices[11] = top_color[2];
			vertices[15] = right_color[0];
			vertices[16] = right_color[1];
			vertices[17] = right_color[2];
			ImGui::End();
		}
		// rendering point
		if (show_point_window)
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
			glPointSize(10.0f);
			glDrawArrays(GL_POINTS, 0, 3);

		}
		// rendering lines
		if (show_line_window)
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(lines), lines, GL_STATIC_DRAW);
			glLineWidth(10.0f);
			glDrawArrays(GL_LINES, 0, 2);
		}

		// 使用EBO(Element Buffer Object)绘制多个三角形
		if (show_severaltriangles_window)
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(severalTriangles), severalTriangles, GL_STATIC_DRAW);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(EBO);
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
