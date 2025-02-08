#pragma once
#include "Transform.h"
#include <GLFW/glfw3.h>

class Camera : public Transform {
private:
    glm::mat4 proj;

	float speed;
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

	Camera(int width, int height);
	void update(GLFWwindow* window, float deltaTime);

	glm::mat4 getProjectionMatrix() {
		return proj;
	};
};