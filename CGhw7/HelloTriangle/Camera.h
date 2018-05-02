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
	glm::vec3 cameraPos; // �����λ��
	glm::vec3 cameraFront; // �����ָ��
	glm::vec3 cameraUp; // ����
	glm::vec3 cameraRight; // ����
	glm::vec3 worldUp;
	GLfloat cameraYaw;
	GLfloat cameraPitch;
	GLfloat cameraSpeed; // WASD
	GLfloat cameraSensitivity; // ���
	GLfloat fov;
	// constructor
 	Camera();
	Camera(glm::vec3 position, glm::vec3 worldup, GLfloat yaw, GLfloat pitch);
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
	void updateCameraVectors();
};

