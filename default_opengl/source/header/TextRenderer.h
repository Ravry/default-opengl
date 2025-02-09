#pragma once
#include "VAO.h"
#include "VBO.h"
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <map>
#include <iostream>

struct Character {
    Texture* texture;
    glm::ivec2   Size;
    glm::ivec2   Bearing;
    unsigned int Advance;
};

class TextRenderer {
private:
    Shader* shaderText;
    std::map<char, Character> Characters;
    VAO* textVAO;
    VBO* textVBO;
public:
	TextRenderer(const char* fontfile, unsigned int fontsize);
	void renderText(Camera* camera, std::string text, glm::vec2 screenPos, float scale, glm::vec3 color);
};