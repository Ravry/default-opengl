#pragma once
#include "glad/glad.h"
#include "../external/stbi/stb_image.h"
#include <iostream>

class Texture {
private:
	unsigned int id;
public:
	Texture(const char* filename, GLint filtermode);
	Texture(int width, int height);
	void bind();
	void unbind();
	void loadFromFile(const char* filename);
	void destroy();
};