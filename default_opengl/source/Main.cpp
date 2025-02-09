#define STB_IMAGE_IMPLEMENTATION
#include "header/Window.h"

int main() {
    const unsigned int WIDTH = 1920/1.5f;
    const unsigned int HEIGHT = 1080/1.5f;
    Window* window = new Window(WIDTH, HEIGHT, "title");
    window->run();
    return 0;
}