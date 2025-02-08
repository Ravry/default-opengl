#pragma once
#include "glad/glad.h"
#include "Texture.h"
#include "RBO.h"

class FBO {
private:
	unsigned int id;
	RBO* rbo;
	Texture* fboTexture;
public:
	FBO(int width, int height);
	void bind();
	void unbind();
	void destroy();

	Texture* getTex() {
		return fboTexture;
	};
};