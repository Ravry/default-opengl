#include "header/Renderer.h"

glm::mat4 proj;
glm::mat4 view;
glm::mat4 model;

Shader* defaultShader;
Texture* tex;
VAO* vao;
VBO* vbo;
EBO* ebo;

Renderer::Renderer(int width, int height) {
    proj = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.01f, 100.0f);
    view = glm::mat4(1.0f);
    model = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(width/2, height/2, -1)), glm::vec3(width/2, height/2, 1));

    defaultShader = new Shader("./shader/default/standard.vert", "./shader/default/standard.frag");
    tex = new Texture("./textures/checkered.png", GL_POINT);

    float vertices[] = {
         0.5f,  0.5f, 0.0f,     1.0f, 1.0f,     // top right
         0.5f, -0.5f, 0.0f,     1.0f, 0.0f,     // bottom right
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f,     // bottom left
        -0.5f,  0.5f, 0.0f,     0.0f, 1.0f,   // top left 
    };

    unsigned int indices[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

	vao = new VAO();
	vbo = new VBO();
	ebo = new EBO();

    vao->bind();

    vbo->bind();
    vbo->data(vertices, sizeof(vertices));

    ebo->bind();
    ebo->data(indices, sizeof(indices));

    vao->attrib(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    vao->attrib(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
}

void Renderer::render() {
    defaultShader->use();
    defaultShader->setMatrix4x4("projection", proj);
    defaultShader->setMatrix4x4("view", view);
    defaultShader->setMatrix4x4("model", model);
    defaultShader->setVec2("_TexTiling", glm::vec2(4, 3));
    defaultShader->setVec4("_TexTint", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

    vao->bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::update_viewport(int width, int height) {
    proj = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.01f, 100.0f);
}

void Renderer::cleanup() {
    vao->destroy();
    vbo->destroy();
    ebo->destroy();
}