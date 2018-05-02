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
#include "Camera.h"
#include "shader.h"
#include <SOIL.h>
using namespace std;

// camera
Camera camera;


bool firstMouse = true;
float lastX = 1200.0f / 2.0;
float lastY = 800.0 / 2.0;
// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Options
GLboolean shadows = true;

// Global variables
GLuint woodTexture;
GLuint planeVAO;


void processInput(GLFWwindow *);
void framebuffer_size_callback(GLFWwindow*, int, int);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

GLuint loadTexture(GLchar* path);
void RenderScene(int &shader);
void RenderCube();

int main() {
	// ��ʼ��GLFW
	glfwInit();
	// ����GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// �������ڶ��󣬴�����кʹ�����ص����ݣ�
	// ���һᱻGLFW����������Ƶ�����õ�
	GLFWwindow* window = glfwCreateWindow(1200, 800, "CGhw7", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	// ֪ͨGLFW�����Ǵ��ڵ�����������Ϊ��ǰ�̵߳���������
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
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

	ImVec4 clear_color = ImVec4(0.00f, 0.00f, 0.00f, 1.0f);


	// ��ɫ��
	int shader = shaderprogram(shadow_mapping_vertex, shadow_mapping_fragment);
	// ����任����ռ���ɫ��
	int simpleDepthShader = shaderprogram(shadow_mapping_depth_vertex, shadow_mapping_depth_fragment);

	// Set texture samples
	glUseProgram(shader);
	glUniform1i(glGetUniformLocation(shader, "diffuseTexture"), 0);
	glUniform1i(glGetUniformLocation(shader, "shadowMap"), 1);

	// ƽ�涥������
	GLfloat planeVertices[] = {
		// Positions        // Normals       // Texture Coords
		25.0f, -0.4f, 25.0f, 0.0f, 1.0f, 0.0f, 25.0f, 0.0f,
		-25.0f, -0.4f, -25.0f, 0.0f, 1.0f, 0.0f, 0.0f, 25.0f,
		-25.0f, -0.4f, 25.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,

		25.0f, -0.4f, 25.0f, 0.0f, 1.0f, 0.0f, 25.0f, 0.0f,
		25.0f, -0.4f, -25.0f, 0.0f, 1.0f, 0.0f, 25.0f, 25.0f,
		-25.0f, -0.4f, -25.0f, 0.0f, 1.0f, 0.0f, 0.0f, 25.0f
	};
	// ƽ����Ⱦ��ʼ��
	GLuint planeVBO;
	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);
	glBindVertexArray(planeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glBindVertexArray(0);

	// ��Դλ��
	glm::vec3 lightPos(-2.0f, 4.0f, -1.0f);

	// ��������
	 woodTexture = loadTexture("./textures/wood.png");
	// ---- �����ͼ ----
	// Ϊ��Ⱦ�������ͼ����һ��֡�������
	GLuint depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);
	// ���������ͼ
	GLuint depthMap;
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1200, 800, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// �����ɵ����������Ϊ֡�������Ȼ���
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	// ��ʾ˵����ʹ���κ���ɫ���ݽ�����Ⱦ
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// GUI��ʼ������
	ImGuiWindowFlags window_flags = 0;
	bool show_01_window = true;
	bool show_02_window = false;
	bool show_03_window = false;
	cout << "render loop" << endl;


	// ��Ⱦѭ�� render loop
	while (!glfwWindowShouldClose(window))
	{
		// Set frame time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(window);
		glfwPollEvents();
		ImGui_ImplGlfwGL3_NewFrame();
		glClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		bool* p_open = NULL;
		// ������-----------------------------------------------------------------------------------
		ImGui::Begin("main", p_open, window_flags);
		window_flags |= ImGuiWindowFlags_MenuBar;
		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("Windows"))
			{
				ImGui::MenuItem("Shadowing Mapping", NULL, &show_01_window);
				if (show_01_window == true)
				{
					show_03_window = false;
					show_02_window = false;
				}
				/*
				ImGui::MenuItem("Gouraud Shading", NULL, &show_02_window);
				if (show_02_window == true)
				{
					show_03_window = false;
					show_01_window = false;
				}
				ImGui::MenuItem("View Changing", NULL, &show_03_window);
				if (show_03_window == true)
				{
					show_02_window = false;
					show_01_window = false;
				}
				*/

				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		/*if (ImGui::CollapsingHeader("Help"))
		{
			ImGui::TextWrapped("Please click 'Windows' to choose different functions. \n\n");
		}*/
		ImGui::Spacing();
		ImGui::Text("push 'q' to hide cursor");
		ImGui::Text("push 'e' to show cursor");
		ImGui::End();

		// Rendering
		int display_w, display_h;

		// glm::vec3 lightPos;
		// ��Ȳ���
		glEnable(GL_DEPTH_TEST);
		if (show_01_window)
		{
			// 1. ��Ⱦ�����ͼ
			// ʹ������ͶӰ����
			glm::mat4 lightProjection, lightView;
			glm::mat4 lightSpaceMatrix;
			// ��Դ�ռ�ı任��ÿ������ռ�����任����Դ���������Ŀռ����꣩
			// ������Ⱦ�����ͼ
			GLfloat near_plane = 1.0f, far_plane = 7.5f;
			lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
			lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
			lightSpaceMatrix = lightProjection * lightView;
			// �ӹ��͸��ͼ����Ⱦ�����������Ϣ
			glUseProgram(simpleDepthShader);
			setMat4(simpleDepthShader, "lightSpaceMatrix", lightSpaceMatrix);
			glViewport(0, 0, display_w, display_h);
			// �洰�ڴ�С�Զ�����
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, display_w, display_h, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
			glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
			glClear(GL_DEPTH_BUFFER_BIT);
			RenderScene(simpleDepthShader);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			// 2. ��Ⱦ����
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glUseProgram(shader);
			glm::mat4 projection = glm::perspective(45.0f, 1.5f, 0.1f, 100.0f);
			glm::mat4 view = camera.GetViewMatrix();
			setMat4(shader, "projection", projection);
			setMat4(shader, "view", view);
			// ����Դ���Ե���ɫ��
			setVec3(shader, "lightPos", lightPos);
			setVec3(shader, "viewPos", camera.cameraPos);
			setMat4(shader, "lightSpaceMatrix", lightSpaceMatrix);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, woodTexture);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, depthMap);
			RenderScene(shader);
		}

		if (show_02_window) {

		}

		if (show_03_window) {

		}
		// Rendering
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
	}

	// �ͷ�/ɾ��֮ǰ�����������Դ
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}


// ��Ⱦ����
void RenderScene(int &shader)
{
	glUseProgram(shader);
	// Floor
	glm::mat4 model;
	setMat4(shader, "model", model);
	glBindVertexArray(planeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	// Cubes
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0));
	setMat4(shader, "model", model);
	RenderCube();
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(1.0f, 0.0f, 1.0));
	setMat4(shader, "model", model);
	RenderCube();
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 2.0));
	model = glm::rotate(model, 45.0f, glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	model = glm::scale(model, glm::vec3(0.5));
	setMat4(shader, "model", model);
	RenderCube();
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0));
	model = glm::scale(model, glm::vec3(0.5));
	setMat4(shader, "model", model);
	RenderCube();
}



// ��Ⱦ������
GLuint cubeVAO = 0;
GLuint cubeVBO = 0;
void RenderCube()
{
	if (cubeVAO == 0)
	{
		GLfloat vertices[] = {
			// Back face
			-0.4f, -0.4f, -0.4f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // Bottom-left
			0.4f, 0.4f, -0.4f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // top-right
			0.4f, -0.4f, -0.4f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
			0.4f, 0.4f, -0.4f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,  // top-right
			-0.4f, -0.4f, -0.4f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,  // bottom-left
			-0.4f, 0.4f, -0.4f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,// top-left
			// Front face
			-0.4f, -0.4f, 0.4f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
			0.4f, -0.4f, 0.4f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,  // bottom-right
			0.4f, 0.4f, 0.4f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,  // top-right
			0.4f, 0.4f, 0.4f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // top-right
			-0.4f, 0.4f, 0.4f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,  // top-left
			-0.4f, -0.4f, 0.4f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom-left
			// Left face
			-0.4f, 0.4f, 0.4f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
			-0.4f, 0.4f, -0.4f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-left
			-0.4f, -0.4f, -0.4f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom-left
			-0.4f, -0.4f, -0.4f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-left
			-0.4f, -0.4f, 0.4f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // bottom-right
			-0.4f, 0.4f, 0.4f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
			// Right face
			0.4f, 0.4f, 0.4f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-left
			0.4f, -0.4f, -0.4f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-right
			0.4f, 0.4f, -0.4f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-right         
			0.4f, -0.4f, -0.4f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom-right
			0.4f, 0.4f, 0.4f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // top-left
			0.4f, -0.4f, 0.4f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom-left     
			// Bottom face
			-0.4f, -0.4f, -0.4f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
			0.4f, -0.4f, -0.4f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, // top-left
			0.4f, -0.4f, 0.4f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,// bottom-left
			0.4f, -0.4f, 0.4f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom-left
			-0.4f, -0.4f, 0.4f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom-right
			-0.4f, -0.4f, -0.4f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
			// Top face
			-0.4f, 0.4f, -0.4f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// top-left
			0.4f, 0.4f, 0.4f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
			0.4f, 0.4f, -0.4f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // top-right     
			0.4f, 0.4f, 0.4f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
			-0.4f, 0.4f, -0.4f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// top-left
			-0.4f, 0.4f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f // bottom-left  
		};
		glGenVertexArrays(1, &cubeVAO);
		glGenBuffers(1, &cubeVBO);
		glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// ���Ӷ�������
		glBindVertexArray(cubeVAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	// ��Ⱦ������
	glBindVertexArray(cubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}


// ���ļ��м�������
GLuint loadTexture(GLchar* path)
{
	// ��������
	// ������������
	GLuint textureID;
	glGenTextures(1, &textureID);
	int width, height;
	unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	// Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
	return textureID;
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
	GLfloat cameraSpeed = 0.05f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.moveForward(deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.moveBack(deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.moveLeft(deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.moveRight(deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) // �������
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) // ��ʾ���
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
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
	camera.ProcessMouseMovement(xoffset, yoffset);
}



// �Դ���ע��һ���ص�������������ÿ�δ��ڴ�С��������ʱ�򱻵���
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// ���ô��ڵ�ά��
	glViewport(0, 0, width, height);
}




