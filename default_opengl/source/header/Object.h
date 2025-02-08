#pragma once
#include <vector>

#include "Transform.h"
#include "Material.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

struct Attrib {
	GLuint layout;
	GLint size;
	GLenum type;
	GLboolean normalized;
	GLsizei stride;
	const void* pointer;

	Attrib(GLuint l, GLint s, GLenum t, GLboolean n, GLsizei st, const void* p) : layout(l), size(s), type(t), normalized(n), stride(st), pointer(p) {}
};

class Object : public Transform {
private:
	Material* material;
	VAO* vao;
	VBO* vbo;
	EBO* ebo;
	unsigned int indicesCount;
public:
	Object(Material* material, std::vector<float>& vertices, std::vector<unsigned int>& indices, std::vector<Attrib*>& attribs);
	Object(Material* material, std::vector<float>& vertices, std::vector<unsigned int>& indices, glm::vec3 pos, glm::vec3 scale, std::vector<Attrib*>& attribs);
	void render(glm::mat4 proj, glm::mat4 view);
	void destroy();
};