#define STB_IMAGE_IMPLEMENTATION
#include "header/Window.h"

int main() {
    const unsigned int WIDTH = 800;
    const unsigned int HEIGHT = 600;
    Window* window = new Window(WIDTH, HEIGHT, "title");
    window->run();
    return 0;
}