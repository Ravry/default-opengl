#include "header/Renderer.h"

Object* quadObject;

Renderer::Renderer(int width, int height) {
    camera = new Camera(width, height);

    std::vector<const char*> cubemap_textures{
        "textures/skybox/right.jpg",
        "textures/skybox/left.jpg",
        "textures/skybox/top.jpg",
        "textures/skybox/bottom.jpg",
        "textures/skybox/front.jpg",
        "textures/skybox/back.jpg"
    };

    std::vector<float> skyboxVertices = {
        -1.0f,  1.0f, -1.0f,  // 0
        -1.0f, -1.0f, -1.0f,  // 1
         1.0f, -1.0f, -1.0f,  // 2
         1.0f,  1.0f, -1.0f,  // 3
        -1.0f,  1.0f,  1.0f,  // 4
        -1.0f, -1.0f,  1.0f,  // 5
         1.0f, -1.0f,  1.0f,  // 6
         1.0f,  1.0f,  1.0f   // 7
    };
    std::vector<unsigned int> skyboxIndices = {
        // Front face
        0, 1, 2,
        2, 3, 0,

        // Left face
        0, 4, 5,
        5, 1, 0,

        // Right face
        3, 2, 6,
        6, 7, 3,

        // Back face
        7, 6, 5,
        5, 4, 7,

        // Top face
        0, 3, 7,
        7, 4, 0,

        // Bottom face
        1, 5, 6,
        6, 2, 1
    };

    Material* skyboxMaterial = new Material(
        new Shader("./shader/cubemap/cubemap.vert", "./shader/cubemap/cubemap.frag"),
        new Texture(cubemap_textures)
    );

    std::vector<Attrib*> skyboxAttribs{
        new Attrib(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0)
    };

    skyboxMaterial->setInt("skybox", 0);

    objects.push_back(
        new Object(skyboxMaterial, skyboxVertices, skyboxIndices, skyboxAttribs)
    );


    Material* material = new Material(
        new Shader("./shader/default/standard.vert", "./shader/default/standard.frag"),
        new Texture("./textures/checkered.png", GL_POINT)
    );

    material->setVec2("_TexTiling", glm::vec2(2, 2));
    material->setVec4("_TexTint", glm::vec4(1, 0, 0, 1));

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

    std::vector<Attrib*> attribs{
        new Attrib(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0),
        new Attrib(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)))
    };

    objects.push_back(
        new Object(material, vertices, indices, attribs)
    );

    /*-----------------*/

    fbo = new FBO(width, height);

    Material* quadMaterial = new Material(
        new Shader("./shader/screen/experimental/raymarch.vert", "./shader/screen/experimental/raymarch.frag"),
        fbo->getTex()
    );

    std::vector<float> quadVertices = {
        -1.0f,  1.0f, 0.0f, 1.0f,  // 0 - Top Left
        -1.0f, -1.0f, 0.0f, 0.0f,  // 1 - Bottom Left
         1.0f, -1.0f, 1.0f, 0.0f,  // 2 - Bottom Right
         1.0f,  1.0f, 1.0f, 1.0f   // 3 - Top Right
    };
    std::vector<unsigned int> quadIndices = {
        0, 1, 2,  // First triangle
        0, 2, 3   // Second triangle
    };

    std::vector<Attrib*> quadAttribs{
        new Attrib(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0),
        new Attrib(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)))
    };

    quadObject = new Object(quadMaterial, quadVertices, quadIndices, quadAttribs);

    glDepthFunc(GL_LEQUAL);
}

void Renderer::render(GLFWwindow* window, float deltaTime) {
    camera->update(window, deltaTime);

    fbo->bind();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    
    for (auto obj : objects)
    {
        //obj->rotate(10.0f * deltaTime, glm::vec3(0, 1, 0));
        obj->applyMaterial(camera->getProjectionMatrix(), camera->getMatrix());
        obj->render();
    }
    
    fbo->unbind();
    glDisable(GL_DEPTH_TEST);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    quadObject->applyMaterial(camera->getProjectionMatrix(), camera->getMatrix());
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    quadObject->getMaterial()->getShader()->SetFloat("_Time", glfwGetTime());
    quadObject->getMaterial()->getShader()->setVec3("_CameraPosition", glm::vec3(camera->position));
    quadObject->getMaterial()->getShader()->setMatrix4x4("_CameraViewMatrix", camera->getMatrix());
    quadObject->getMaterial()->getShader()->setMatrix4x4("_CameraProjectionMatrix", camera->getProjectionMatrix());
    quadObject->render();

    //std::cout << 1.0f / deltaTime << std::endl;
}

void Renderer::update_viewport(int width, int height) {
    //proj = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.01f, 100.0f);
}

void Renderer::cleanup() {
    for (auto obj : objects)
        obj->destroy();

    fbo->destroy();
}