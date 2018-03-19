#include <glad/glad.h>
#include <GLFW/glfw3.h>
/*GLAD的头文件包含了正确的OpenGL头文件（例如GL/gl.h），
所以需要在其它依赖于OpenGL的头文件之前包含GLAD。*/
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include <stdio.h>
#include <iostream>
#include"Triangle.h"
using namespace std;
// -----------------------------------------------------
// 常量值
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// 顶点着色器源码
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   ourColor = aColor;\n"
"}\0";
// 片段着色器源码
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor, 1.0f);\n"
"}\n\0";

// -----------------------------------------------------
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
// -----------------------------------------------------

int Hello_Triangle()
{
	// 初始化GLFW
	glfwInit();
	// 配置GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 创建窗口对象，存放所有和窗口相关的数据，
	// 而且会被GLFW的其他函数频繁地用到
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "HellloTriangle", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	// 通知GLFW将我们窗口的上下文设置为当前线程的主上下文
	glfwMakeContextCurrent(window);
	// 注册这个函数，告诉GLFW我们希望每当窗口调整大小的时候调用这个函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// GLAD: 管理的OpenGL函数指针
	// 调用任何OpenGL函数之前需要初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

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
	// 3. 链接着色器
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

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// positions         // colors
		0.5f, -0.2f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom right
		-0.5f, -0.2f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
		0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f    // top 

	};
	// 顶点缓冲对象，顶点数组对象
	unsigned int VBO;
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// 绑定顶点数组对象
	glBindVertexArray(VAO);
	// 把我们的顶点数组复制到一个顶点缓冲中，供OpenGL使用
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 链接顶点属性
	// 位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// 颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// 激活着色器程序对象
	glUseProgram(shaderProgram);
	//-----------------------
	// 渲染循环 render loop
	while (!glfwWindowShouldClose(window))
	{
		// 输入
		processInput(window);
		// 渲染指令
		// 设置清空屏幕所用颜色
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// 渲染三角形
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// 交换缓冲
		glfwSwapBuffers(window);
		// 检查有没有触发什么事件、更新窗口状态，并调用对应的回调函数
		glfwPollEvents();
	}

	// 释放/删除之前分配的所有资源
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}

