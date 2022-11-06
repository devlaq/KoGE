#include "shader.h"
#include "../util/resources.h"

void Shader::load(std::string vertexShaderPath, std::string fragmentShaderPath) {
    Resources::parse({&vertexShaderPath, &fragmentShaderPath});
    std::ifstream vertexShaderFile, fragmentShaderFile;

	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vertexShaderFile.open(vertexShaderPath);
		fragmentShaderFile.open(fragmentShaderPath);

		std::stringstream vertexShaderStream, fragmentShaderStream;

		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();

		vertexShaderFile.close();
		fragmentShaderFile.close();

		vertexShaderCode = vertexShaderStream.str();
		fragmentShaderCode = fragmentShaderStream.str();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "[Shader|Error] Exception occured while reading shader file: " << e.what() << std::endl;
	}
}

void Shader::link() {
    std::cout << "[Shader] Compiling shader" << std::endl;
    const char* vertexShaderCode_ = vertexShaderCode.c_str();
    const char* fragmentShaderCode_ = fragmentShaderCode.c_str();

    unsigned int vertexId, fragmentId;
    int isSuccess;
    char infoLog[512];

    vertexId = glCreateShader(GL_VERTEX_SHADER);
    fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertexId, 1, &vertexShaderCode_, nullptr);
    glShaderSource(fragmentId, 1, &fragmentShaderCode_, nullptr);

    glCompileShader(vertexId);
    glCompileShader(fragmentId);

    glGetShaderiv(vertexId, GL_COMPILE_STATUS, &isSuccess);
	if (!isSuccess) {
		glGetShaderInfoLog(vertexId, 512, nullptr, infoLog);
		std::cout << "[Shader|Error] Vertex shader compilation failed.\n" << infoLog << std::endl;
	}
	glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &isSuccess);
	if (!isSuccess) {
		glGetShaderInfoLog(fragmentId, 512, nullptr, infoLog);
		std::cout << "[Shader|Error] Fragment shader compilation failed.\n" << infoLog << std::endl;
	}

    std::cout << "[Shader] Linking shaders" << std::endl;
    id = glCreateProgram();
	glAttachShader(id, vertexId);
	glAttachShader(id, fragmentId);
	glLinkProgram(id);

	glGetProgramiv(id, GL_LINK_STATUS, &isSuccess);
	if (!isSuccess) {
		glGetProgramInfoLog(id, 512, nullptr, infoLog);
		std::cout << "[Shader|Error] Program linking failed.\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);

    std::cout << "[Shader] Compiled and linked shaders" << std::endl;
}

void Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int) value);
}
void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::use() const {
    glUseProgram(id);
}

int Shader::getUniformLocation(const std::string &name) const {
    return glGetUniformLocation(id, name.c_str());
}

void Shader::loadAndLink(const std::string &vertexShaderPath, const std::string &fragmentShaderPath) {
    load(vertexShaderPath, fragmentShaderPath);
    link();
}
