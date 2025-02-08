#pragma once
#include "Shader.h"
#include "Texture.h"

class Material {
private:
	Shader* shader;
	Texture* tex;
public:
	Material(Shader* s, Texture* t);
	void destroy();

	Shader* getShader() {
		return shader;
	}

	Texture* getTex() {
		return tex;
	}
};