#pragma once
#include "Shader.h"
#include "Texture.h"
#include <unordered_map>

class Material {
private:
	Shader* shader;
	Texture* tex;

	std::unordered_map<const char*, int> intUniforms;
	std::unordered_map<const char*, glm::vec4> vec4Uniforms;
	std::unordered_map<const char*, glm::vec2> vec2Uniforms;
public:
	Material(Shader* s, Texture* t);

	void setVec4(const char* name, glm::vec4 value) { vec4Uniforms[name] = value; }
	void setVec2(const char* name, glm::vec2 value) { vec2Uniforms[name] = value; }
	void setInt(const char* name, int value) { intUniforms[name] = value; }
	
	void apply(glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
		shader->use();
		shader->setMatrix4x4("model", model);
		shader->setMatrix4x4("view", view);
		shader->setMatrix4x4("projection", projection);
		
		for (const auto& [name, value] : intUniforms) shader->SetInt(name, value);
		for (const auto& [name, value] : vec4Uniforms) shader->setVec4(name, value);
		for (const auto& [name, value] : vec2Uniforms) shader->setVec2(name, value);
		
		if (tex) tex->bind();
	}

	void unbind() {
		if (tex) tex->unbind();
		shader->unuse();
	}

	void destroy();

	Shader* getShader() {
		return shader;
	}

	Texture* getTex() {
		return tex;
	}
};