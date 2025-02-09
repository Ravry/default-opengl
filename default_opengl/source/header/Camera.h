#pragma once
#include "Transform.h"
#include <GLFW/glfw3.h>

class Camera : public Transform {
private:
	float fov;
	glm::mat4 proj;
	glm::mat4 projOrtho;

	float speed;
	float speedMultiplier;
	float yaw;
	float pitch;
	float sens;

	float lastX, lastY;
public:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUP;

	Camera(int width, int height, float fov);
	void update(GLFWwindow* window, float deltaTime);
	void handleKeyboardInput(GLFWwindow* window, float deltaTime);
	void handleMouseInput(GLFWwindow* window);
	void refactorProjection(int width, int height);

	glm::mat4 getProjectionMatrix() {
		return proj;
	};

	glm::mat4 getProjectionOrtho() {
		return projOrtho;
	}
};