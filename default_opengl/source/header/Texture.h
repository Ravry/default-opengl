#pragma once
#include "glad/glad.h"
#include "../external/stbi/stb_image.h"
#include <iostream>
#include <vector>

class Texture {
private:
	unsigned int id;
public:
	Texture(const char* filename, GLint filtermode);
	Texture(int width, int height);
	Texture(int width, int heigth, const void* pixels);
	Texture(std::vector<const char*>& cubemap_textures);
	void bind();
	void unbind();
	void loadFromFile(const char* filename);
	void destroy();
	unsigned int getID() {
		return id;
	};
};