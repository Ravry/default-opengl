#include "header/Object.h"

Object::Object(Material* material, std::vector<float>& vertices, std::vector<unsigned int>& indices, std::vector<Attrib*>& attribs) : Transform() {
	this->material = material;
	this->indicesCount = indices.size();

	vao = new VAO();
	vbo = new VBO();
	ebo = new EBO();

	vao->bind();

	vbo->bind();
	vbo->data(vertices.data(), vertices.size() * sizeof(float));

	ebo->bind();
	ebo->data(indices.data(), indices.size() * sizeof(unsigned int));

	for (auto _attrib : attribs)
		vao->attrib(_attrib->layout, _attrib->size, _attrib->type, _attrib->normalized, _attrib->stride, _attrib->pointer);

	vbo->unbind();
	ebo->unbind();
	vao->unbind();
}

Object::Object(Material* material, std::vector<float>& vertices, std::vector<unsigned int>& indices, glm::vec3 pos, glm::vec3 s, std::vector<Attrib*>& attribs) : Transform() {
	this->material = material;
	this->indicesCount = indices.size();
	
	vao = new VAO();
	vbo = new VBO();
	ebo = new EBO();

	vao->bind();

	vbo->bind();
	vbo->data(vertices.data(), vertices.size() * sizeof(float));

	ebo->bind();
	ebo->data(indices.data(), indices.size() * sizeof(unsigned int));

	for (auto _attrib : attribs)
		vao->attrib(_attrib->layout, _attrib->size, _attrib->type, _attrib->normalized, _attrib->stride, _attrib->pointer);
	
	ebo->unbind();
	vbo->unbind();
	vao->unbind();

	move(pos);
	scale(s);
}

void Object::applyMaterial(glm::mat4 proj, glm::mat4 view) {
	material->apply(mat, view, proj);
}

void Object::render()
{
	vao->bind();
	ebo->bind();
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
	ebo->unbind();
	vao->unbind();

	material->unbind();
}

void Object::destroy() {
	vao->destroy();
	vbo->destroy();
	ebo->destroy();
	material->destroy();
}