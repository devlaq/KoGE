//
// Created by devla on 2022-11-03.
//

#include "font.h"
#include "fonts.h"
#include "../../graphic/graphics.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtc/type_ptr.hpp"

void Font::render(const std::string& text, float x, float y, float scale, glm::vec3 color) {
    Shader renderShader = Fonts::renderShader;
    renderShader.use();

    glUniform3f(renderShader.getUniformLocation("textColor"), color.x, color.y, color.z);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glActiveTexture(GL_TEXTURE2);
    glBindVertexArray(VAO);

    std::string::const_iterator c;
    for(c = text.begin(); c != text.end(); c++) {
        Glyph glyph = glyphs.find(*c)->second;

        float xPos = x + glyph.bearing.x * scale;
        float yPos = y - (glyph.size.y - glyph.bearing.y) * scale;

        float w = glyph.size.x * scale;
        float h = glyph.size.y * scale;

        float vertices[6][4] = {
                { xPos, yPos + h, 0.0f, 0.0f },
                { xPos, yPos, 0.0f, 1.0f },
                { xPos + w, yPos, 0.0f, 1.0f },

                { xPos, yPos + h, 0.0f, 0.0f },
                { xPos + w, yPos, 1.0f, 1.0f },
                { xPos + w, yPos + h, 1.0f, 1.0f }
        };

        glBindTexture(GL_TEXTURE_2D, glyph.textureId);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        x += (glyph.advance >> 6) * scale;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Font::Font() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(Graphics::screenWidth), 0.0f, static_cast<float>(Graphics::screenHeight));
    Fonts::renderShader.use();
    glUniformMatrix4fv(glGetUniformLocation(Fonts::renderShader.id, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
}

Font::~Font() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}