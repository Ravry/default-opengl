#pragma once

#include <glm/glm.hpp>
#include "Object.h"

class Renderer {
private:
public:
	Renderer(int width, int height);
	void render();
	void cleanup();
	void update_viewport(int width, int height);
};