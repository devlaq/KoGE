//
// Created by devla on 2022-11-05.
//

#ifndef KORPG_TEXTURE_H
#define KORPG_TEXTURE_H

#include <string>

#ifndef __glad_h_
#include "glad/glad.h"
#endif
#include <GLFW/glfw3.h>

#include <memory>
#include "../stb_image.h"

#include "../util/resources.h"
#include "spdlog/logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"


class Texture {
private:
    static std::shared_ptr<spdlog::logger> logger;
public:
    unsigned int textureId{};
    int bindToUnit;
    GLenum bindToType;

    Texture(int bindToUnit, GLenum bindToType);
    ~Texture();

    void load(std::string path, GLenum format, GLenum dataType);
    void bind(int unit, GLenum type);
    void bind();
};

#endif //KORPG_TEXTURE_H
