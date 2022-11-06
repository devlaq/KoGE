//
// Created by devla on 2022-11-03.
//

#ifndef KORPG_GLYPH_H
#define KORPG_GLYPH_H

#include "glm/glm.hpp"

class Glyph {
public:
    Glyph(unsigned int textureId, glm::ivec2 size, glm::ivec2 bearing, unsigned int advance): textureId(textureId), size(size), bearing(bearing), advance(advance) {

    }

    glm::ivec2 bearing;
    glm::ivec2 size;
    unsigned int textureId;
    unsigned int advance;
};


#endif //KORPG_GLYPH_H
