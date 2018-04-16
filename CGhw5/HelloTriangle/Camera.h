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
	glm::vec3 cameraPos; // �����λ��
	glm::vec3 cameraFront; // �����ָ��
	glm::vec3 cameraUp; // ����
	glm::vec3 cameraRight; // ����
	glm::vec3 worldUp;
=======
// �������������
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
	GLfloat cameraSensitivity; // ���
<<<<<<< HEAD
=======

>>>>>>> d8e0237d1e00f910b41b724232fdb0012882bc6d
	GLfloat fov;
	// constructor
 	Camera();
	Camera(glm::vec3 position, glm::vec3 worldup, GLfloat yaw, GLfloat pitch);
<<<<<<< HEAD
	// WASD�ƶ�
	void moveForward(GLfloat deltaTime);
	void moveBack(GLfloat deltaTime);
	void moveLeft(GLfloat deltaTime);
	void moveRight(GLfloat deltaTime);
	// ����ƶ������ӽ�
	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset);
	// ���ɹ۲����
	glm::mat4 GetViewMatrix();
private:
	// �������ݳ�Ա
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

