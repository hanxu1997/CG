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

<<<<<<< HEAD
class Camera {
public:
	glm::vec3 cameraPos; // 摄像机位置
	glm::vec3 cameraFront; // 摄像机指向
	glm::vec3 cameraUp; // 右轴
	glm::vec3 cameraRight; // 上轴
	glm::vec3 worldUp;
=======
// 定义摄像机变量
class Camera {
public:
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;
	glm::vec3 worldUp;

>>>>>>> d8e0237d1e00f910b41b724232fdb0012882bc6d
	GLfloat cameraYaw;
	GLfloat cameraPitch;
	GLfloat cameraSpeed; // WASD
	GLfloat cameraSensitivity; // 鼠标
<<<<<<< HEAD
=======

>>>>>>> d8e0237d1e00f910b41b724232fdb0012882bc6d
	GLfloat fov;
	// constructor
 	Camera();
	Camera(glm::vec3 position, glm::vec3 worldup, GLfloat yaw, GLfloat pitch);
<<<<<<< HEAD
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
=======
	void moveForward(GLfloat deltaTime);
	void moveBack(GLfloat deltaTime);
	void moveRight(GLfloat deltaTime);
	void moveLeft(GLfloat deltaTime);
	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset);
	// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix();
private:
>>>>>>> d8e0237d1e00f910b41b724232fdb0012882bc6d
	void updateCameraVectors();
};

