#pragma once
#include "glad/glad.h"

class VBO {
private:
	unsigned int id;
public:
	VBO();
	void bind();
	void unbind();
	void data(float* vertices, size_t size, GLenum usage = GL_STATIC_DRAW);
	void destroy();
};