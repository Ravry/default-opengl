#include "header/Cubemap.h"

Cubemap::Cubemap(std::vector<const char*>& textures_faces) {
	texture = new Texture(textures_faces);
}