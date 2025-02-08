#pragma once
#include <glm/glm.hpp>
#include "Object.h"
#include "FBO.h"
#include "Camera.h"
#include "Cubemap.h"

class Renderer {
private:
	std::vector<Object*> objects;
public:
	Renderer(int width, int height);
	void render(GLFWwindow* window, float deltaTime);
	void cleanup();
	void update_viewport(int width, int height);
};