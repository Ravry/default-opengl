#pragma once
#include "glad/glad.h"

class VAO {
private:
	unsigned int id;
public:
	VAO();
	void bind();
	void unbind();
	void attrib(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
	void destroy();
};
