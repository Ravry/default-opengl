#include "header/Material.h"

Material::Material(Shader* s, Texture* t) {
	shader = s;
	tex = t;
}

void Material::destroy() {
	shader->destroy();
	tex->destroy();
}