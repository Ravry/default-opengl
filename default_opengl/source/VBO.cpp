#include "header/VBO.h"

VBO::VBO() {
	glGenBuffers(1, &id);
}

void VBO::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VBO::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::data(float* vertices, size_t size, GLenum usage) {
	glBufferData(GL_ARRAY_BUFFER, size, vertices, usage);
}

void VBO::destroy() {
	glDeleteBuffers(1, &id);
}