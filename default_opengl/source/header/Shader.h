#pragma once
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class Shader {
private:
	unsigned int id;
public:
	Shader(const char* vertexFile, const char* fragmentFile);
	void use();
	void unuse();
	void setMatrix4x4(const char* uniform, glm::mat4 matrix);
	void setVec2(const char* uniform, glm::vec2 vec);
	void setVec4(const char* uniform, glm::vec4 vec);
	void SetInt(const char* uniform, int val);
	void destroy();
};