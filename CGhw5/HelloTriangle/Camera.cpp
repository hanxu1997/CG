#include "Camera.h"

Camera::Camera() {
	this->cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	this->cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->cameraRight = glm::normalize(glm::cross(cameraUp, cameraPos));
	this->worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

	this->cameraYaw = -90.0f;
	this->cameraPitch = 0.0f;
	this->cameraSpeed = 2.0f; // WASD
	this->cameraSensitivity = 0.02f; // ЪѓБъ
	this->fov = 45.0f;
}

Camera::Camera(glm::vec3 position, glm::vec3 worldup, GLfloat yaw, GLfloat pitch) {
	this->cameraPos = position;
	this->worldUp = worldup;
	this->cameraYaw = yaw;
	this->cameraPitch = pitch;
	this->updateCameraVectors();
}

// W
void Camera::moveForward(GLfloat deltaTime) {
	GLfloat v = this->cameraSpeed * deltaTime;
	this->cameraPos += v * this->cameraFront;
}

// A
void Camera::moveBack(GLfloat deltaTime) {
	GLfloat v = this->cameraSpeed * deltaTime;
	this->cameraPos -= v * cameraFront;
}
 
// S
void Camera::moveLeft(GLfloat deltaTime) {
	GLfloat v = this->cameraSpeed * deltaTime;
	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * v;
}
// D
void Camera::moveRight(GLfloat deltaTime) {
	GLfloat v = this->cameraSpeed * deltaTime;
	this->cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp))* v;
}

void Camera::moveLeft(GLfloat deltaTime) {
	GLfloat v = this->cameraSpeed * deltaTime;
	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * v;
}

void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset) {
	xoffset *= this->cameraSensitivity;
	yoffset *= this->cameraSensitivity;
	this->cameraYaw += xoffset;
	this->cameraPitch += yoffset;
	if (this->cameraPitch > 89.0f) {
		this->cameraPitch = 89.0f;
	}
	if (this->cameraPitch < -89.0f) {
		this->cameraPitch = -89.0f;
	}
	this->updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(this->cameraPos, this->cameraPos + this->cameraFront, this->cameraUp);
}

void Camera::updateCameraVectors() {
	glm::vec3 front;
	front.x = cos(glm::radians(this->cameraYaw)) * cos(glm::radians(this->cameraPitch));
	front.y = sin(glm::radians(this->cameraPitch));
	front.z = sin(glm::radians(this->cameraYaw)) * cos(glm::radians(this->cameraPitch));
	this->cameraFront = glm::normalize(front);
	this->cameraRight = glm::normalize(glm::cross(this->cameraFront, this->worldUp));
	this->cameraUp = glm::normalize(glm::cross(this->cameraRight, this->cameraFront));
}
