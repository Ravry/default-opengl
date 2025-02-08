#include "header/Renderer.h"

Camera* cam;

Shader* skyboxShader;
Cubemap* cubemap;
VAO* skyboxVAO;
VBO* skyboxVBO;

Shader* screenShader;
VAO* quadVAO;
VBO* quadVBO;
FBO* fbo;

Renderer::Renderer(int width, int height) {
    cam = new Camera(width, height);

    skyboxShader = new Shader("./shader/cubemap/cubemap.vert", "./shader/cubemap/cubemap.frag");
    std::vector<const char*> cubemap_textures{
        "textures/skybox/right.jpg",
        "textures/skybox/left.jpg",
        "textures/skybox/top.jpg",
        "textures/skybox/bottom.jpg",
        "textures/skybox/front.jpg",
        "textures/skybox/back.jpg"
    };
    cubemap = new Cubemap(cubemap_textures);

    float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    skyboxVAO = new VAO();
    skyboxVBO = new VBO();

    skyboxVAO->bind();
    skyboxVBO->bind();

    skyboxVBO->data(skyboxVertices, sizeof(skyboxVertices));
    skyboxVAO->attrib(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    skyboxVBO->unbind();
    skyboxVAO->unbind();


    Material* material = new Material(
        new Shader("./shader/default/standard.vert", "./shader/default/standard.frag"),
        new Texture("./textures/checkered.png", GL_POINT)
    );

    std::vector<float> vertices = {
         //vertex               //uv
         0.5f,  0.5f, 0.0f,     1.0f, 1.0f,     // top right
         0.5f, -0.5f, 0.0f,     1.0f, 0.0f,     // bottom right
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f,     // bottom left
        -0.5f,  0.5f, 0.0f,     0.0f, 1.0f,     // top left 
    };

    std::vector<unsigned int> indices = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    objects.push_back(
        new Object(material, vertices, indices, glm::vec3(0), glm::vec3(1))
    );


    screenShader = new Shader("./shader/screen/screen.vert", "./shader/screen/screen.frag");

    float quadVertices[] = {
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

    quadVAO = new VAO();
    quadVBO = new VBO();

    quadVAO->bind();
    quadVBO->bind();

    quadVBO->data(quadVertices, sizeof(quadVertices));

    quadVAO->attrib(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    quadVAO->attrib(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    quadVBO->unbind();
    quadVAO->unbind();

    fbo = new FBO(width, height);
}

void Renderer::render(GLFWwindow* window, float deltaTime) {
    cam->update(window, deltaTime);

    fbo->bind();
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto obj : objects)
    {
        obj->rotate(10.0f * deltaTime, glm::vec3(0, 1, 0));
        obj->render(cam->getProjectionMatrix(), cam->getMatrix());
    }

    glDepthFunc(GL_LEQUAL);
    skyboxShader->use();
    skyboxShader->SetInt("skybox", 0);
    skyboxShader->setMatrix4x4("view", glm::mat4(glm::mat3(cam->getMatrix())));
    skyboxShader->setMatrix4x4("projection", cam->getProjectionMatrix());
    skyboxVAO->bind();
    glActiveTexture(GL_TEXTURE0);
    cubemap->getTexture()->bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    skyboxVAO->unbind();

    fbo->unbind();
    glDisable(GL_DEPTH_TEST);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    screenShader->use();
    quadVAO->bind();
    fbo->getTex()->bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    //std::cout << 1.0f / deltaTime << std::endl;
}

void Renderer::update_viewport(int width, int height) {
    //proj = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.01f, 100.0f);
}

void Renderer::cleanup() {
    for (auto obj : objects)
        obj->destroy();
}