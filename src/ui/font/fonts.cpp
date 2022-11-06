//
// Created by devla on 2022-11-03.
//

#include "fonts.h"
#include "../../util/resources.h"

FT_Library Fonts::freetype;
std::map<std::string, Font> Fonts::fonts;
Shader Fonts::renderShader = Shader();

void Fonts::init() {
    initFreeType();
    renderShader.loadAndLink("res://shader/textShader.frag", "res://shader/textShader.frag");
}

void Fonts::initFreeType() {
    if(freetype) {
        std::cout << "[Fonts] Error: Freetype already initialized" << std::endl;
        return;
    }

    FT_Init_FreeType(&freetype);
}

void Fonts::loadFont(const std::string &name, std::string path) {
    Resources::parse({&path});

    FT_Face face;
    if(FT_New_Face(freetype, path.c_str(), 0, &face)) {
        std::cout << "[Fonts] Error: Failed to load font from \"" << path << "\"" << std::endl;
        return;
    }

    Font font;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    for(unsigned char c = 0; c < 128; c++) {
        if(FT_Load_Glyph(face, c, FT_LOAD_RENDER)) {
            std::cout << "[Fonts] Error: Failed to load glyph";
            continue;
        }

        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
                );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Glyph glyph = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
        };
        font.glyphs.insert(std::pair<char, Glyph>(c, glyph));
    }

    fonts.insert(std::pair<std::string, Font>(name, font));
}

void Fonts::dispose() {
    FT_Done_FreeType(freetype);
}

Font Fonts::get(std::string name) {
    return fonts[name];
}



