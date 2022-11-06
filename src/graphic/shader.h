#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	unsigned int id{};
    std::string vertexShaderCode;
    std::string fragmentShaderCode;

    Shader() = default;
    Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
        loadAndLink(vertexShaderPath, fragmentShaderPath);
    }

    void load(std::string vertexShaderPath, std::string fragmentShaderPath);
    void link();
    void loadAndLink(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);

    void use() const;

    int getUniformLocation(const std::string& name) const;
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;

	void setFloat(const std::string& name, float value) const;
};

