#include "header/Window.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Window::Window(unsigned int width, unsigned int height, const char* title) {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glViewport(0, 0, width, height);
    glfwSetWindowUserPointer(window, this);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* win, int w, int h) {
        Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(win));
        if (instance)
        {
            instance->getRenderer()->update_viewport(w, h);
        }
        glViewport(0, 0, w, h);
    });

    renderer = new Renderer(width, height);
}

void Window::run() {
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        renderer->render();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    renderer->cleanup();
    glfwTerminate();
}