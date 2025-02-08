#pragma once
#include <vector>

#include "Transform.h"
#include "Material.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Object : public Transform {
private:
	Material* material;
	VAO* vao;
	VBO* vbo;
	EBO* ebo;
public:
	Object(Material* material, std::vector<float>& vertices, std::vector<unsigned int>& indices);
	Object(Material* material, std::vector<float>& vertices, std::vector<unsigned int>& indices, glm::vec3 pos, glm::vec3 scale);
	void render(glm::mat4 proj, glm::mat4 view);
	void destroy();
};