//
// Created by devla on 2022-11-03.
//

#ifndef KORPG_FONT_H
#define KORPG_FONT_H


#include <map>
#include <string>
#include "glyph.h"

class Font {
private:
    unsigned int VAO{}, VBO{};
public:
    Font();
    ~Font();

    std::map<char, Glyph> glyphs;

    void render(const std::string& text, float x, float y, float scale, glm::vec3 color);
};


#endif //KORPG_FONT_H
