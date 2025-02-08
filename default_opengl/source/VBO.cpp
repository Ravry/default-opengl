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

void VBO::data(float* vertices, size_t size) {
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::destroy() {
	glDeleteBuffers(1, &id);
}