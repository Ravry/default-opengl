#include "header/Camera.h"

Camera::Camera(int width, int height, float fov) : Transform() {
    this->fov = fov;
    this->speed = 5.0f;
    this->speedMultiplier = 1.0f;
    this->position = glm::vec3(0);
    this->worldUP = glm::vec3(0, 1, 0);
    this->yaw = -90.0f;
    this->pitch = 0.0f;
    this->lastX = width / 2.0f;
    this->lastY = height / 2.0f;
    this->sens = .05f;

    this->proj = glm::perspective(glm::radians(this->fov), (float)width / (float)height, 0.1f, 100.0f);
    this->projOrtho = glm::ortho(0.0f, (float)width, 0.0f, (float)height);
}

void Camera::update(GLFWwindow* window, float deltaTime) {
    handleMouseInput(window);
    handleKeyboardInput(window, deltaTime);
    
    mat = glm::lookAt(position, position + front, up);
}

void Camera::handleKeyboardInput(GLFWwindow* window, float deltaTime) {
    glm::vec3 _direction = glm::vec3(0);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        _direction.z += 1;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        _direction.z -= 1;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        _direction.x -= 1;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        _direction.x += 1;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        _direction.y += 1;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        _direction.y -= 1;
    }

    if (glm::length(_direction) != 0) {
        _direction = glm::normalize(_direction);
    }

    speedMultiplier = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) ? 2.0f : 1.0f;

    position += (_direction.x * right + _direction.y * worldUP + _direction.z * front) * deltaTime * speed * speedMultiplier;
}

void Camera::handleMouseInput(GLFWwindow* window) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    xoffset *= sens;
    yoffset *= sens;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    glm::vec3 _front;
    _front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    _front.y = sin(glm::radians(pitch));
    _front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(_front);
    right = glm::normalize(glm::cross(front, worldUP));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::refactorProjection(int width, int height) {
    proj = glm::perspective(glm::radians(this->fov), (float)width / (float)height, 0.1f, 100.0f);
    projOrtho = glm::ortho(0.0f, (float)width, 0.0f, (float)height);
}