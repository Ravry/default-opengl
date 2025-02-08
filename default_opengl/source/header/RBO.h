#pragma once
#include "glad/glad.h"

class RBO {
private:
	unsigned int id;
public:
	RBO(int width, int height);
	void bind();
	void unbind();
	unsigned int getID() {
		return id;
	};
};