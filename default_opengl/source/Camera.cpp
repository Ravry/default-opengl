#include "header/Camera.h"

Camera::Camera(int width, int height) : Transform() {
    //proj = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.01f, 100.0f);
    proj = glm::perspective(glm::radians(60.0f), (float)width / (float)height, 0.1f, 100.0f);
    speed = 5.0f;
    position = glm::vec3(0);
    worldUP = glm::vec3(0, 1, 0);
    yaw = -90.0f;
    pitch = 0.0f;
    lastX = width / 2.0f;
    lastY = height / 2.0f;
    sens = .05f;
}

void Camera::update(GLFWwindow* window, float deltaTime) {
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

    right = glm::normalize(glm::cross(front, worldUP));  // Right vector (perpendicular to front and worldUp)
    up = glm::normalize(glm::cross(right, front));       // Up vector (perpendicular to right and front)

    glm::vec3 _direction = glm::vec3(0);

    // Handle keyboard input for camera movement
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
    position += (_direction.x * right + _direction.y * up + _direction.z * front) * deltaTime * speed;

    mat = glm::lookAt(position, position + front, up);
}
