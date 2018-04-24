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
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
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

	// ImVec4 clear_color = ImVec4(0.92f, 0.92f, 0.92f, 1.0f);
	ImVec4 clear_color = ImVec4(0.00f, 0.00f, 0.00f, 1.0f);

	int phongCubeShader = shaderprogram(phongVertexShader, phongFragmentShader);
	int gauraudCubeShader = shaderprogram(gouraudVertexShader, gouraudFragmentShader);
	int phongLightShader = shaderprogram(lightvertex, lightfragment);
	

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
	cout << "render loop" << endl;
	// phong
	float ambientStrength = 0.1f;
	float specularStrength = 0.5f;
	float diffuseStrength = 1.0f;
	float shinines = 32.0f; // 反光度
	bool phone_reset = false;

	glm::vec3 lightPos = glm::vec3(0.4f, 0.4f, 1.0f);
	glm::vec3 runLightPos;

	// 渲染循环 render loop
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
		// 主窗口-----------------------------------------------------------------------------------
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
				}
				ImGui::MenuItem("Gouraud Shading", NULL, &show_gouraud_window);
				if (show_gouraud_window == true)
				{
					show_viewchanging_window = false;
					show_phong_window = false;
				}
				ImGui::MenuItem("View Changing", NULL, &show_viewchanging_window);
				if (show_viewchanging_window == true)
				{
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
		// 主窗口绘制完成--------------------------------------------------------------------------	
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		glm::vec3 objectColor;
		glm::vec3 lightColor;
		
		
		// glm::vec3 lightPos;
		// 深度测试
		glEnable(GL_DEPTH_TEST);
		if (show_phong_window)
		{
			ImGui::Begin("Phong Shading", &show_phong_window);
			ImGui::SliderFloat("ambientStrength", &ambientStrength, 0.0f, 1.0f);
			ImGui::SliderFloat("diffuseStrength", &diffuseStrength, 0.0f, 5.0f);
			ImGui::SliderFloat("specularStrength", &specularStrength, 0.0f, 2.0f);
			ImGui::SliderFloat("shinines", &shinines, 0.0f, 100.0f);
			ImGui::SliderFloat("lightX", &lightPos.x, -20.0f, 20.0f);
			ImGui::SliderFloat("lightY", &lightPos.y, -20.0f, 20.0f);
			ImGui::SliderFloat("lightZ", &lightPos.z, -20.0f, 20.0f);
			ImGui::Checkbox("remain unchanged", &phone_reset);
			if (phone_reset) {
				ambientStrength = 0.1f;
				specularStrength = 0.5f;
				diffuseStrength = 1.0f;
				shinines = 32.0f; // 反光度
				lightPos = glm::vec3(0.4f, 0.4f, 1.0f);
			}
			// cube
			glUseProgram(phongCubeShader);
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
			view = camera.GetViewMatrix();
			projection = glm::perspective(45.0f, 1.5f, 0.1f, 100.0f);
			objectColor = glm::vec3(0.66f, 0.66f, 1.00f);
			lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
			
			setMat4(phongCubeShader, "model", model);
			setMat4(phongCubeShader, "view", view);
			setMat4(phongCubeShader, "projection", projection);
			setVec3(phongCubeShader, "objectColor", objectColor);
			setVec3(phongCubeShader, "lightColor", lightColor);
			setVec3(phongCubeShader, "lightPos", lightPos);
			setVec3(phongCubeShader, "viewPos", camera.cameraPos);
			setFloat(phongCubeShader, "ambientStrength", ambientStrength);
			setFloat(phongCubeShader, "diffuseStrength", diffuseStrength);
			setFloat(phongCubeShader, "specularStrength", specularStrength);
			setFloat(phongCubeShader, "shinines", shinines);
			
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glBindVertexArray(cubeVAO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			// light
			glUseProgram(phongLightShader);	
			model = glm::mat4();
			model = glm::translate(model, lightPos);
			model = glm::scale(model, glm::vec3(0.2f));
			setMat4(phongLightShader, "model", model);
			setMat4(phongLightShader, "view", view);
			setMat4(phongLightShader, "projection", projection);
			glBindVertexArray(lightVAO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			ImGui::End();
		}
	
		if (show_gouraud_window) {
			ImGui::Begin("Gouraud Shading", &show_phong_window);
			ImGui::SliderFloat("ambientStrength", &ambientStrength, 0.0f, 1.0f);
			ImGui::SliderFloat("diffuseStrength", &diffuseStrength, 0.0f, 5.0f);
			ImGui::SliderFloat("specularStrength", &specularStrength, 0.0f, 2.0f);
			ImGui::SliderFloat("shinines", &shinines, 0.0f, 100.0f);
			ImGui::SliderFloat("lightX", &lightPos.x, -20.0f, 20.0f);
			ImGui::SliderFloat("lightY", &lightPos.y, -20.0f, 20.0f);
			ImGui::SliderFloat("lightZ", &lightPos.z, -20.0f, 20.0f);
			ImGui::Checkbox("remain unchanged", &phone_reset);
			if (phone_reset) {
				ambientStrength = 0.1f;
				specularStrength = 0.5f;
				diffuseStrength = 1.0f;
				shinines = 32.0f; // 反光度
				lightPos = glm::vec3(0.4f, 0.4f, 1.0f);
			}
			// cube
			glUseProgram(gauraudCubeShader);
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
			view = camera.GetViewMatrix();
			projection = glm::perspective(45.0f, 1.5f, 0.1f, 100.0f);
			objectColor = glm::vec3(0.66f, 0.66f, 1.00f);
			lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
			
			setMat4(gauraudCubeShader, "model", model);
			setMat4(gauraudCubeShader, "view", view);
			setMat4(gauraudCubeShader, "projection", projection);
			setVec3(gauraudCubeShader, "objectColor", objectColor);
			setVec3(gauraudCubeShader, "lightColor", lightColor);
			setVec3(gauraudCubeShader, "lightPos", lightPos);
			setVec3(gauraudCubeShader, "viewPos", camera.cameraPos);
			setFloat(gauraudCubeShader, "ambientStrength", ambientStrength);
			setFloat(gauraudCubeShader, "diffuseStrength", diffuseStrength);
			setFloat(gauraudCubeShader, "specularStrength", specularStrength);
			setFloat(gauraudCubeShader, "shinines", shinines);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glBindVertexArray(cubeVAO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			// light
			glUseProgram(phongLightShader);
			model = glm::mat4();
			model = glm::translate(model, lightPos);
			model = glm::scale(model, glm::vec3(0.2f));
			setMat4(phongLightShader, "model", model);
			setMat4(phongLightShader, "view", view);
			setMat4(phongLightShader, "projection", projection);
			glBindVertexArray(lightVAO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			ImGui::End();
		}

		if (show_viewchanging_window) {
			ImGui::Begin("Phong Shading", &show_phong_window);
			ImGui::SliderFloat("ambientStrength", &ambientStrength, 0.0f, 1.0f);
			ImGui::SliderFloat("diffuseStrength", &diffuseStrength, 0.0f, 5.0f);
			ImGui::SliderFloat("specularStrength", &specularStrength, 0.0f, 2.0f);
			ImGui::SliderFloat("shinines", &shinines, 0.0f, 100.0f);
			ImGui::Checkbox("remain unchanged", &phone_reset);
			if (phone_reset) {
				ambientStrength = 0.1f;
				specularStrength = 0.5f;
				diffuseStrength = 1.0f;
				shinines = 32.0f; // 反光度
			}
			// cube
			glUseProgram(phongCubeShader);
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
			view = camera.GetViewMatrix();
			projection = glm::perspective(45.0f, 1.5f, 0.1f, 100.0f);
			objectColor = glm::vec3(0.66f, 0.66f, 1.00f);
			lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

			setMat4(phongCubeShader, "model", model);
			setMat4(phongCubeShader, "view", view);
			setMat4(phongCubeShader, "projection", projection);
			setVec3(phongCubeShader, "objectColor", objectColor);
			setVec3(phongCubeShader, "lightColor", lightColor);
			setVec3(phongCubeShader, "lightPos", runLightPos);
			setVec3(phongCubeShader, "viewPos", camera.cameraPos);
			setFloat(phongCubeShader, "ambientStrength", ambientStrength);
			setFloat(phongCubeShader, "diffuseStrength", diffuseStrength);
			setFloat(phongCubeShader, "specularStrength", specularStrength);
			setFloat(phongCubeShader, "shinines", shinines);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glBindVertexArray(cubeVAO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			// light
			glUseProgram(phongLightShader);
			model = glm::mat4();
			runLightPos.x = sin(glfwGetTime()) * 0.5f;
			runLightPos.y = cos(glfwGetTime()) * 0.5f;
			runLightPos.z = 1.0f;
			model = glm::translate(model, runLightPos);
			model = glm::scale(model, glm::vec3(0.2f));
			setMat4(phongLightShader, "model", model);
			setMat4(phongLightShader, "view", view);
			setMat4(phongLightShader, "projection", projection);
			glBindVertexArray(lightVAO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glDrawArrays(GL_TRIANGLES, 0, 36);
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
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &lightVAO);
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



// 对窗口注册一个回调函数，它会在每次窗口大小被调整的时候被调用
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// 设置窗口的维度
	glViewport(0, 0, width, height);
}




