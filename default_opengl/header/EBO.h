#pragma once
#include "glad/glad.h"

class EBO {
private:
	unsigned int id;
public:
	EBO();
	void bind();
	void unbind();
	void data(unsigned int* indices, size_t size);
	void destroy();
};