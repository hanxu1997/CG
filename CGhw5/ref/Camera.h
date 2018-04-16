#pragma once
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
const glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

class Camera {
public:
	void moveForward(GLfloat const distance);
	void moveBack(GLfloat const distance);
	void moveRight(GLfloat const distance);
	void moveLeft(GLfloat const distance);
    void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true)
    // Returns the view matrix calculated using Eular Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix();
private:
	GLfloat pfov, partio, pnear, pfar;
	GLfloat cameraPosX, cameraPosY, cameraPosZ;
	GLfloat cameraFrontX, cameraFrontY, cameraFrontZ;
	GLfloat cameraRightX, cameraRightY, cameraRightZ;
	GLfloat cameraUpX, cameraUpY, CameraUpZ;
	void updateCameraVectors();
};

glm::mat4 GetViewMatrix() {
    return glm::lookAt(this->Position, this->Position + this->Front, this->Up);
}