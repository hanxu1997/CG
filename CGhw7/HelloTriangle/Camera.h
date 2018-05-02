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

class Camera {
public:
	glm::vec3 cameraPos; // 摄像机位置
	glm::vec3 cameraFront; // 摄像机指向
	glm::vec3 cameraUp; // 右轴
	glm::vec3 cameraRight; // 上轴
	glm::vec3 worldUp;
	GLfloat cameraYaw;
	GLfloat cameraPitch;
	GLfloat cameraSpeed; // WASD
	GLfloat cameraSensitivity; // 鼠标
	GLfloat fov;
	// constructor
 	Camera();
	Camera(glm::vec3 position, glm::vec3 worldup, GLfloat yaw, GLfloat pitch);
	// WASD移动
	void moveForward(GLfloat deltaTime);
	void moveBack(GLfloat deltaTime);
	void moveLeft(GLfloat deltaTime);
	void moveRight(GLfloat deltaTime);
	// 鼠标移动调整视角
	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset);
	// 生成观察矩阵
	glm::mat4 GetViewMatrix();
	
private:
	// 更新数据成员
	void updateCameraVectors();
};

