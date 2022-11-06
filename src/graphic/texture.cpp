//
// Created by devla on 2022-11-05.
//

#include "texture.h"
#include "spdlog/sinks/stdout_color_sinks.h"

std::shared_ptr<spdlog::logger> Texture::logger = spdlog::stdout_color_mt("Texture");

Texture::Texture(int bindToUnit, GLenum bindToType): bindToUnit(bindToUnit), bindToType(bindToType) {

}

Texture::~Texture() {
    glDeleteTextures(1, &textureId);
}

void Texture::load(std::string path, GLenum format, GLenum dataType) {
    Resources::parse(&path);

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if(data) {
        glTexImage2D(bindToType, 0, format, width, height, 0, format, dataType, data);
        glGenerateMipmap(bindToType);
    } else {
        logger->error("Failed to load texture: ", stbi_failure_reason());
    }
    stbi_image_free(data);
}

void Texture::bind(int unit, GLenum type) {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(type, textureId);
}

void Texture::bind() {
    bind(bindToUnit, bindToType);
}
