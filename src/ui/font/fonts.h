//
// Created by devla on 2022-11-03.
//

#ifndef KORPG_FONTS_H
#define KORPG_FONTS_H

#include <iostream>
#include <map>

#ifndef __glad_h_
#include "glad/glad.h"
#endif
#include "GLFW/glfw3.h"

#include "ft2build.h"
#include FT_FREETYPE_H
#include "font.h"
#include "../../graphic/shader.h"

class Fonts {
private:
    static FT_Library freetype;
    static std::map<std::string, Font> fonts;
public:
    static Shader renderShader;

    static void init();
    static void initFreeType();
    static void loadFont(const std::string& name, std::string path);
    static void dispose();

    static Font get(std::string name);
};


#endif //KORPG_FONTS_H
