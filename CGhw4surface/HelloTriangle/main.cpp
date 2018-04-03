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
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

// ������ɫ��Դ��
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
// Ƭ����ɫ��Դ��
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// ��ɫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
/*
	float vertices[] = {
		//     ---- λ�� ----       ---- ��ɫ ----   
		-0.3f, -0.3f, 0.0f,  0.0f, 0.0f, 1.0f,
		0.3f, -0.3f,  0.0f,  0.0f, 0.0f, 1.0f,
		0.3f,  0.3f,  0.0f,  0.0f, 0.0f, 1.0f,
		0.3f,  0.3f,  0.0f,  1.0f, 0.0f, 0.0f,
		-0.3f,  0.3f,  0.0f,  1.0f, 0.0f, 0.0f,
		-0.3f, -0.3f,  0.0f,  1.0f, 0.0f, 0.0f,
	};
	*/
	// ������λ�ú���ɫ
	float vertices[] = {
		-0.4f, -0.4f, -0.4f,  0.0f, 0.0f, 0.0f,
		0.4f, -0.4f, -0.4f,  1.0f, 0.0f, 0.0f,
		0.4f,  0.4f, -0.4f,  1.0f, 1.0f, 0.0f,
		0.4f,  0.4f, -0.4f,  1.0f, 1.0f, 0.0f,
		-0.4f,  0.4f, -0.4f,  0.0f, 1.0f, 0.0f,
		-0.4f, -0.4f, -0.4f,  0.0f, 0.0f, 0.0f,

		-0.4f, -0.4f,  0.4f,  0.0f, 0.0f, 0.0f,
		0.4f, -0.4f,  0.4f,  1.0f, 0.0f, 0.0f,
		0.4f,  0.4f,  0.4f,  1.0f, 1.0f, 0.0f,
		0.4f,  0.4f,  0.4f,  1.0f, 1.0f, 0.0f,
		-0.4f,  0.4f,  0.4f,  0.0f, 1.0f, 0.0f,
		-0.4f, -0.4f,  0.4f,  0.0f, 0.0f, 0.0f,

		-0.4f,  0.4f,  0.4f,  1.0f, 0.0f, 0.0f,
		-0.4f,  0.4f, -0.4f,  1.0f, 1.0f, 0.0f,
		-0.4f, -0.4f, -0.4f,  0.0f, 1.0f, 0.0f,
		-0.4f, -0.4f, -0.4f,  0.0f, 1.0f, 0.0f,
		-0.4f, -0.4f,  0.4f,  0.0f, 0.0f, 0.0f,
		-0.4f,  0.4f,  0.4f,  1.0f, 0.0f, 0.0f,

		0.4f,  0.4f,  0.4f,  1.0f, 0.0f, 0.0f,
		0.4f,  0.4f, -0.4f,  1.0f, 1.0f, 0.0f,
		0.4f, -0.4f, -0.4f,  0.0f, 1.0f, 0.0f,
		0.4f, -0.4f, -0.4f,  0.0f, 1.0f, 0.0f,
		0.4f, -0.4f,  0.4f,  0.0f, 0.0f, 0.0f,
		0.4f,  0.4f,  0.4f,  1.0f, 0.0f, 0.0f,

		-0.4f, -0.4f, -0.4f,  0.0f, 1.0f, 0.0f,
		0.4f, -0.4f, -0.4f,  1.0f, 1.0f, 0.0f,
		0.4f, -0.4f,  0.4f,  1.0f, 0.0f, 0.0f,
		0.4f, -0.4f,  0.4f,  1.0f, 0.0f, 0.0f,
		-0.4f, -0.4f,  0.4f,  0.0f, 0.0f, 0.0f,
		-0.4f, -0.4f, -0.4f,  0.0f, 1.0f, 0.0f,

		-0.4f,  0.4f, -0.4f,  0.0f, 1.0f, 0.0f,
		0.4f,  0.4f, -0.4f,  1.0f, 1.0f, 0.0f,
		0.4f,  0.4f,  0.4f,  1.0f, 0.0f, 0.0f,
		0.4f,  0.4f,  0.4f,  1.0f, 0.0f, 0.0f,
		-0.4f,  0.4f,  0.4f,  0.0f, 0.0f, 0.0f,
		-0.4f,  0.4f, -0.4f,  0.0f, 1.0f, 0.0f
	};
	
	ImGuiWindowFlags window_flags = 0;
	bool show_triangle_window = true;
	bool show_circle_window = false;
	bool show_rasterization_window = false;
	// ��ȣ�
	glEnable(GL_DEPTH_TEST);
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
			glm::mat4 model;
			glm::mat4 view;
			glm::mat4 projection;
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
			glDrawArrays(GL_TRIANGLES, 0, 36);
			ImGui::End();
		}
		// rendering points
		if (show_circle_window)
		{
			ImGui::Begin("Circle Window", &show_circle_window);
			ImGui::End();

		}
		if (show_rasterization_window) {
			ImGui::Begin("Rasterization Window", &show_rasterization_window);
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
