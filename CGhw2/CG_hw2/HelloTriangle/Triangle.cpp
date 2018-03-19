#include <glad/glad.h>
#include <GLFW/glfw3.h>
/*GLAD��ͷ�ļ���������ȷ��OpenGLͷ�ļ�������GL/gl.h����
������Ҫ������������OpenGL��ͷ�ļ�֮ǰ����GLAD��*/
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include <stdio.h>
#include <iostream>
#include"Triangle.h"
using namespace std;
// -----------------------------------------------------
// ����ֵ
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// ������ɫ��Դ��
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   ourColor = aColor;\n"
"}\0";
// Ƭ����ɫ��Դ��
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor, 1.0f);\n"
"}\n\0";

// -----------------------------------------------------
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
// -----------------------------------------------------

int Hello_Triangle()
{
	// ��ʼ��GLFW
	glfwInit();
	// ����GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// �������ڶ��󣬴�����кʹ�����ص����ݣ�
	// ���һᱻGLFW����������Ƶ�����õ�
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "HellloTriangle", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	// ֪ͨGLFW�����Ǵ��ڵ�����������Ϊ��ǰ�̵߳���������
	glfwMakeContextCurrent(window);
	// ע���������������GLFW����ϣ��ÿ�����ڵ�����С��ʱ������������
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// GLAD: �����OpenGL����ָ��
	// �����κ�OpenGL����֮ǰ��Ҫ��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

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
	// 3. ������ɫ��
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

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// positions         // colors
		0.5f, -0.2f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom right
		-0.5f, -0.2f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
		0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f    // top 

	};
	// ���㻺����󣬶����������
	unsigned int VBO;
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// �󶨶����������
	glBindVertexArray(VAO);
	// �����ǵĶ������鸴�Ƶ�һ�����㻺���У���OpenGLʹ��
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// ���Ӷ�������
	// λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// ��ɫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// ������ɫ���������
	glUseProgram(shaderProgram);
	//-----------------------
	// ��Ⱦѭ�� render loop
	while (!glfwWindowShouldClose(window))
	{
		// ����
		processInput(window);
		// ��Ⱦָ��
		// ���������Ļ������ɫ
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// ��Ⱦ������
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// ��������
		glfwSwapBuffers(window);
		// �����û�д���ʲô�¼������´���״̬�������ö�Ӧ�Ļص�����
		glfwPollEvents();
	}

	// �ͷ�/ɾ��֮ǰ�����������Դ
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}

