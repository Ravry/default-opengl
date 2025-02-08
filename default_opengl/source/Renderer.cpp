#include "header/Renderer.h"

glm::mat4 proj;
glm::mat4 view;

Material* material;
Object* object;

Renderer::Renderer(int width, int height) {
    proj = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.01f, 100.0f);
    view = glm::mat4(1.0f);
    
    material = new Material(
        new Shader("./shader/default/standard.vert", "./shader/default/standard.frag"),
        new Texture("./textures/checkered.png", GL_POINT)
    );

    std::vector<float> vertices = {
         0.5f,  0.5f, 0.0f,     1.0f, 1.0f,     // top right
         0.5f, -0.5f, 0.0f,     1.0f, 0.0f,     // bottom right
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f,     // bottom left
        -0.5f,  0.5f, 0.0f,     0.0f, 1.0f,   // top left 
    };

    std::vector<unsigned int> indices = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    object = new Object(material, vertices, indices, glm::vec3(width/2, height/2, -1), glm::vec3(width/2, height/2, 1));
}

void Renderer::render() {
    object->render(proj, view);
}

void Renderer::update_viewport(int width, int height) {
    proj = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.01f, 100.0f);
}

void Renderer::cleanup() {
    object->destroy();
}