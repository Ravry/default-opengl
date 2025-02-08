#pragma once

#include <glm/glm.hpp>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "Shader.h"

class Renderer {
private:
public:
	Renderer(int width, int height);
	void render();
	void cleanup();
	void update_viewport(int width, int height);
};