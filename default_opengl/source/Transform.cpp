#include "header/Transform.h"

Transform::Transform() {
	mat = glm::mat4(1);
}

void Transform::rotate(float deg, glm::vec3 axis) {
	mat = glm::rotate(mat, glm::radians(deg), axis);
}

void Transform::move(glm::vec3 vec) {
	mat = glm::translate(mat, vec);
}

void Transform::scale(glm::vec3 s) {
	mat = glm::scale(mat, s);
}