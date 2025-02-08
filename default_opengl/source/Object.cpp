#include "header/Object.h"

Object::Object(Material* material, std::vector<float>& vertices, std::vector<unsigned int>& indices) : Transform() {
	this->material = material;

	vao = new VAO();
	vbo = new VBO();
	ebo = new EBO();

	vao->bind();

	vbo->bind();
	vbo->data(vertices.data(), vertices.size() * sizeof(float));

	ebo->bind();
	ebo->data(indices.data(), indices.size() * sizeof(unsigned int));

	vao->attrib(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	vao->attrib(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
}

Object::Object(Material* material, std::vector<float>& vertices, std::vector<unsigned int>& indices, glm::vec3 pos, glm::vec3 s) : Transform() {
	this->material = material;
	
	vao = new VAO();
	vbo = new VBO();
	ebo = new EBO();

	vao->bind();

	vbo->bind();
	vbo->data(vertices.data(), vertices.size() * sizeof(float));

	ebo->bind();
	ebo->data(indices.data(), indices.size() * sizeof(unsigned int));

	vao->attrib(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	vao->attrib(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	
	ebo->unbind();
	vbo->unbind();
	vao->unbind();

	move(pos);
	scale(s);
}

void Object::render(glm::mat4 proj, glm::mat4 view) {
	material->getShader()->use();
	material->getShader()->setMatrix4x4("projection", proj);
	material->getShader()->setMatrix4x4("view", view);
	material->getShader()->setMatrix4x4("model", mat);
	material->getShader()->setVec2("_TexTiling", glm::vec2(2, 2));
	material->getShader()->setVec4("_TexTint", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	material->getTex()->bind();

	vao->bind();
	ebo->bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	ebo->unbind();
	vao->unbind();

	material->getTex()->unbind();
	material->getShader()->unuse();
}

void Object::destroy() {
	vao->destroy();
	vbo->destroy();
	ebo->destroy();
	material->destroy();
}