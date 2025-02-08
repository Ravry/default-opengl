#pragma once
#include "glad/glad.h"
#include "Texture.h"
#include <vector>

class Cubemap {
private:
	Texture* texture;
public:
	Cubemap(std::vector<const char*>& textures_faces);
	Texture* getTexture() {
		return texture;
	};
};