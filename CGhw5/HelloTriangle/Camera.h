#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// 定义摄像机变量
class Camera {
public:
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;
	glm::vec3 worldUp;

	GLfloat cameraYaw;
	GLfloat cameraPitch;
	GLfloat cameraSpeed; // WASD
	GLfloat cameraSensitivity; // 鼠标

	GLfloat fov;
	// constructor
 	Camera();
	Camera(glm::vec3 position, glm::vec3 worldup, GLfloat yaw, GLfloat pitch);
	void moveForward(GLfloat deltaTime);
	void moveBack(GLfloat deltaTime);
	void moveRight(GLfloat deltaTime);
	void moveLeft(GLfloat deltaTime);
	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset);
	// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix();
private:
	void updateCameraVectors();
};

