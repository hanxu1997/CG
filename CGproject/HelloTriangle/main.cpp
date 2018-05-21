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
#include <SOIL.h>
#include "filesystem.h"
#include "Camera.h"
#include "shader.h"
#include "mesh.h"
#include "model.h"

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


int main() {
	// ��ʼ��GLFW
	glfwInit();
	// ����GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// �������ڶ��󣬴�����кʹ�����ص����ݣ�
	// ���һᱻGLFW����������Ƶ�����õ�
	GLFWwindow* window = glfwCreateWindow(1200, 800, "CGproject", NULL, NULL);
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



	////////////////////////////////////////
	int ourShader = shaderprogram(model_loading_vertex, model_loading_fragment);
	int asteroidShader = shaderprogram(asteroids_vertex, asteroids_fragment);
	int planetShader = shaderprogram(planet_vertex, planet_fragment);

	Model ourModel(FileSystem::getPath("../objects/planet/planet.obj"));
	Model rock(FileSystem::getPath("../objects/rock/rock.obj"));
	Model planet(FileSystem::getPath("../objects/planet/planet.obj"));
	// generate a large list of semi-random model transformation matrices
	// ------------------------------------------------------------------
	unsigned int amount = 10000;
	glm::mat4* modelMatrices;
	modelMatrices = new glm::mat4[amount];
	srand(glfwGetTime()); // initialize random seed	
	float radius = 50.0;
	float offset = 10.0f;
	for (unsigned int i = 0; i < amount; i++)
	{
		glm::mat4 model;
		// 1. translation: displace along circle with 'radius' in range [-offset, offset]
		float angle = (float)i / (float)amount * 360.0f;
		float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float x = sin(angle) * radius + displacement;
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float y = displacement * 0.4f; // keep height of asteroid field smaller compared to width of x and z
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float z = cos(angle) * radius + displacement;
		model = glm::translate(model, glm::vec3(x, y, z));

		// 2. scale: Scale between 0.05 and 0.25f
		float scale = (rand() % 20) / 100.0f + 0.05;
		model = glm::scale(model, glm::vec3(scale));

		// 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
		float rotAngle = (rand() % 360);
		model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

		// 4. now add to list of matrices
		modelMatrices[i] = model;
	}

	// configure instanced array
	// -------------------------
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

	// set transformation matrices as an instance vertex attribute (with divisor 1)
	// note: we're cheating a little by taking the, now publicly declared, VAO of the model's mesh(es) and adding new vertexAttribPointers
	// normally you'd want to do this in a more organized fashion, but for learning purposes this will do.
	// -----------------------------------------------------------------------------------------------------------------------------------
	for (unsigned int i = 0; i < rock.meshes.size(); i++)
	{
		unsigned int VAO = rock.meshes[i].VAO;
		glBindVertexArray(VAO);
		// set attribute pointers for matrix (4 times vec4)
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);

		glBindVertexArray(0);
	}

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
				ImGui::MenuItem("planet", NULL, &show_01_window);
				if (show_01_window == true)
				{
					show_03_window = false;
					show_02_window = false;
				}

				ImGui::MenuItem("asteroid", NULL, &show_02_window);
				if (show_02_window == true)
				{
					show_03_window = false;
					show_01_window = false;
				}
				/*
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
			glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			// don't forget to enable shader before setting uniforms
			glUseProgram(ourShader);

			// view/projection transformations
			glm::mat4 projection = glm::perspective(45.0f, 1.5f, 0.1f, 100.0f);
			glm::mat4 view = camera.GetViewMatrix();
			setMat4(ourShader, "projection", projection);
			setMat4(ourShader, "view", view);

			// render the loaded model
			glm::mat4 model;
			//model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
			model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));	// it's a bit too big for our scene, so scale it down
			setMat4(ourShader, "model", model);
			ourModel.Draw(ourShader);
		}

		if (show_02_window) {
			// render
			// ------
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// configure transformation matrices
			glm::mat4 projection = glm::perspective(45.0f, 1.5f, 0.1f, 1000.0f);
			glm::mat4 view = camera.GetViewMatrix();
			glUseProgram(asteroidShader);
			setMat4(asteroidShader, "projection", projection);
			setMat4(asteroidShader, "view", view);
			glUseProgram(planetShader);
			setMat4(planetShader, "projection", projection);
			setMat4(planetShader, "view", view);

			// draw planet
			glm::mat4 model;
			model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
			model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
			setMat4(planetShader, "model", model);
			planet.Draw(planetShader);

			// draw meteorites
			glUseProgram(asteroidShader);
			setInt(asteroidShader, "texture_diffuse1", 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, rock.textures_loaded[0].id); // note: we also made the textures_loaded vector public (instead of private) from the model class.
			for (unsigned int i = 0; i < rock.meshes.size(); i++)
			{
				glBindVertexArray(rock.meshes[i].VAO);
				glDrawElementsInstanced(GL_TRIANGLES, rock.meshes[i].indices.size(), GL_UNSIGNED_INT, 0, amount);
				glBindVertexArray(0);
			}

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




