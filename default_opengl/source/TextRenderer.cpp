#include "header/TextRenderer.h"

TextRenderer::TextRenderer(const char* fontfile, unsigned int fontsize) {
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return;
    }

    FT_Face face;
    if (FT_New_Face(ft, fontfile, 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, fontsize);

    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
    {
        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
        return;
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    for (unsigned char c = 0; c < 128; c++)
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }

        Texture* charTex = new Texture(face->glyph->bitmap.width, face->glyph->bitmap.rows, face->glyph->bitmap.buffer);

        Character character = {
            charTex,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        Characters.insert(std::pair<char, Character>(c, character));
    }
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    textVAO = new VAO();
    textVBO = new VBO();

    textVAO->bind();
    textVBO->bind();

    textVBO->data(NULL, sizeof(float) * 6 * 4, GL_DYNAMIC_DRAW);

    textVAO->attrib(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    textVBO->unbind();
    textVAO->unbind();

    shaderText = new Shader("./shader/text/text.vert", "./shader/text/text.frag");
}

void TextRenderer::renderText(Camera* camera, std::string text, glm::vec2 screenPos, float scale, glm::vec3 color) {
    shaderText->use();
    shaderText->setVec3("textColor", color);
    shaderText->setMatrix4x4("projection", camera->getProjectionOrtho());

    textVAO->bind();

    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        float xpos = screenPos.x + ch.Bearing.x * scale;
        float ypos = screenPos.y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;

        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        ch.texture->bind();
        textVBO->bind();
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        textVBO->unbind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        screenPos.x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }

    textVAO->unbind();
    glBindTexture(GL_TEXTURE_2D, 0);

}