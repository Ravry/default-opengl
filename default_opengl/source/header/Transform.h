#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transform {
protected:
	glm::mat4 mat;
public:
	Transform();
	void move(glm::vec3 vec);
	void rotate(float deg, glm::vec3 axis);
	void scale(glm::vec3 scale);
};