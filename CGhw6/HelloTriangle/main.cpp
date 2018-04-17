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

using namespace std;

// camera
Camera camera;
bool firstMouse = true;
float lastX = 1200.0f / 2.0;
float lastY = 800.0 / 2.0;
// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;
void processInput(GLFWwindow *);
void framebuffer_size_callback(GLFWwindow*, int, int);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);



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

	// ImVec4 clear_color = ImVec4(0.92f, 0.92f, 0.92f, 1.0f);
	ImVec4 clear_color = ImVec4(0.00f, 0.00f, 0.00f, 1.0f);

	int cubeShader = shaderprogram(vertexShaderSource, fragmentShaderSource);


	int lightShader = shaderprogram(lightvertex, lightfragment);

    float vertices[] = {
        -0.4f, -0.4f, -0.4f,  0.0f,  0.0f, -1.0f,
         0.4f, -0.4f, -0.4f,  0.0f,  0.0f, -1.0f,
         0.4f,  0.4f, -0.4f,  0.0f,  0.0f, -1.0f,
         0.4f,  0.4f, -0.4f,  0.0f,  0.0f, -1.0f,
        -0.4f,  0.4f, -0.4f,  0.0f,  0.0f, -1.0f,
        -0.4f, -0.4f, -0.4f,  0.0f,  0.0f, -1.0f,

        -0.4f, -0.4f,  0.4f,  0.0f,  0.0f,  1.0f,
         0.4f, -0.4f,  0.4f,  0.0f,  0.0f,  1.0f,
         0.4f,  0.4f,  0.4f,  0.0f,  0.0f,  1.0f,
         0.4f,  0.4f,  0.4f,  0.0f,  0.0f,  1.0f,
        -0.4f,  0.4f,  0.4f,  0.0f,  0.0f,  1.0f,
        -0.4f, -0.4f,  0.4f,  0.0f,  0.0f,  1.0f,

        -0.4f,  0.4f,  0.4f, -1.0f,  0.0f,  0.0f,
        -0.4f,  0.4f, -0.4f, -1.0f,  0.0f,  0.0f,
        -0.4f, -0.4f, -0.4f, -1.0f,  0.0f,  0.0f,
        -0.4f, -0.4f, -0.4f, -1.0f,  0.0f,  0.0f,
        -0.4f, -0.4f,  0.4f, -1.0f,  0.0f,  0.0f,
        -0.4f,  0.4f,  0.4f, -1.0f,  0.0f,  0.0f,

         0.4f,  0.4f,  0.4f,  1.0f,  0.0f,  0.0f,
         0.4f,  0.4f, -0.4f,  1.0f,  0.0f,  0.0f,
         0.4f, -0.4f, -0.4f,  1.0f,  0.0f,  0.0f,
         0.4f, -0.4f, -0.4f,  1.0f,  0.0f,  0.0f,
         0.4f, -0.4f,  0.4f,  1.0f,  0.0f,  0.0f,
         0.4f,  0.4f,  0.4f,  1.0f,  0.0f,  0.0f,

        -0.4f, -0.4f, -0.4f,  0.0f, -1.0f,  0.0f,
         0.4f, -0.4f, -0.4f,  0.0f, -1.0f,  0.0f,
         0.4f, -0.4f,  0.4f,  0.0f, -1.0f,  0.0f,
         0.4f, -0.4f,  0.4f,  0.0f, -1.0f,  0.0f,
        -0.4f, -0.4f,  0.4f,  0.0f, -1.0f,  0.0f,
        -0.4f, -0.4f, -0.4f,  0.0f, -1.0f,  0.0f,

        -0.4f,  0.4f, -0.4f,  0.0f,  1.0f,  0.0f,
         0.4f,  0.4f, -0.4f,  0.0f,  1.0f,  0.0f,
         0.4f,  0.4f,  0.4f,  0.0f,  1.0f,  0.0f,
         0.4f,  0.4f,  0.4f,  0.0f,  1.0f,  0.0f,
        -0.4f,  0.4f,  0.4f,  0.0f,  1.0f,  0.0f,
        -0.4f,  0.4f, -0.4f,  0.0f,  1.0f,  0.0f
    };

    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // second, configure the light's VAO (VBO stays the same; 
	// the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

	float ortho_left = -4.0f,
		ortho_right = 4.0f,
		ortho_bottom = -4.0f,
		ortho_top = 4.0f,
		ortho_near = 0.1f,
		ortho_far = 10.0f;
	float pres_fov = 45.0f,
		pres_ratio = 1.5f,
		pres_near = 0.1f,
		pres_far = 100.0f;
	ImGuiWindowFlags window_flags = 0;
	bool show_phong_window = true;
	bool show_gouraud_window = false;
	bool show_viewchanging_window = false;
	bool show_camera_window = false;
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
				ImGui::MenuItem("Phong Shading", NULL, &show_phong_window);
				if (show_phong_window == true)
				{
					show_viewchanging_window = false;
					show_gouraud_window = false;
					show_camera_window = false;
				}
				ImGui::MenuItem("Gouraud Shading", NULL, &show_gouraud_window);
				if (show_gouraud_window == true)
				{
					show_viewchanging_window = false;
					show_phong_window = false;
					show_camera_window = false;
				}
				ImGui::MenuItem("View Changing", NULL, &show_viewchanging_window);
				if (show_viewchanging_window == true)
				{
					show_gouraud_window = false;
					show_phong_window = false;
					show_camera_window = false;
				}
				ImGui::MenuItem("Camera Class", NULL, &show_camera_window);
				if (show_camera_window == true)
				{
					show_viewchanging_window = false;
					show_gouraud_window = false;
					show_phong_window = false;
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
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		glm::vec3 objectColor;
		glm::vec3 lightColor;
		glm::vec3 lightPos;
		// glm::vec3 lightPos;
		// ��Ȳ���
		glEnable(GL_DEPTH_TEST);
		if (show_phong_window)
		{
			// cube
			glUseProgram(cubeShader);
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
			view = camera.GetViewMatrix();
			projection = glm::perspective(45.0f, 1.5f, 0.1f, 100.0f);
			objectColor = glm::vec3(0.66f, 0.66f, 1.00f);
			lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
			lightPos = glm::vec3(0.4f, 0.5f, 1.0f);
			setMat4(cubeShader, "model", model);
			setMat4(cubeShader, "view", view);
			setMat4(cubeShader, "projection", projection);
			setVec3(cubeShader, "objectColor", objectColor);
			setVec3(cubeShader, "lightColor", lightColor);
			setVec3(cubeShader, "lightPos", lightPos);
			setVec3(cubeShader, "viewPos", camera.cameraPos);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glBindVertexArray(cubeVAO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			// light
			glUseProgram(lightShader);	
			model = glm::mat4();
			model = glm::translate(model, lightPos);
			model = glm::scale(model, glm::vec3(0.2f));
			setMat4(lightShader, "model", model);
			setMat4(lightShader, "view", view);
			setMat4(lightShader, "projection", projection);
			glBindVertexArray(lightVAO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	
		if (show_gouraud_window) {

		}

		if (show_viewchanging_window) {
		}
		if (show_camera_window) {

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
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &lightVAO);
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
	GLfloat cameraSpeed = 0.05f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.moveForward(deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.moveBack(deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.moveLeft(deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.moveRight(deltaTime);
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




