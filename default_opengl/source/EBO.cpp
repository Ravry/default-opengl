#include "header/EBO.h"

EBO::EBO() {
	glGenBuffers(1, &id);
}

void EBO::bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void EBO::unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::data(unsigned int* indices, size_t size) {
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::destroy() {
	glDeleteBuffers(1, &id);
}