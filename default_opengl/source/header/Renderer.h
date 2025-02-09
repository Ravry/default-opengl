#pragma once
#include "Object.h"
#include "FBO.h"
#include "Camera.h"
#include "TextRenderer.h"

class Renderer {
private:
	std::vector<Object*> objects;
public:
	Camera* camera;
	FBO* fbo;

	Renderer(int width, int height);
	void render(GLFWwindow* window, float deltaTime);
	void cleanup();
	void update_viewport(int width, int height);
};