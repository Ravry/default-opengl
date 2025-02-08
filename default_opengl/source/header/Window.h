#pragma once
#include <iostream>

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "Renderer.h"

class Window {
private:
	GLFWwindow* window;
	Renderer* renderer;
public:
	Window(unsigned int width, unsigned int height, const char* title);
	void run();

	Renderer* getRenderer() {
		return renderer;
	};
};