
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>
#include <string>

#include "graphic/shader.h"
#include "stb_image.h"

#include "./time.h"
#include "graphic/camera/perspectiveCamera.h"
#include "graphic/camera/cameraController.h"
#include "ui/font/fonts.h"
#include "graphic/graphics.h"
#include "util/resources.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "graphic/texture.h"

#include <spdlog/spdlog.h>

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouseCallback(GLFWwindow* window, double x, double y);
std::pair<int, int> getScreenSize();

PerspectiveCamera camera;
CameraController cameraController(&camera);

auto logger = spdlog::stdout_color_mt("main");

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(Graphics::screenWidth, Graphics::screenHeight, "KoRPG", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        logger->critical("Failed to initialize GLAD");
	}

    logger->set_error_handler([](const std::string& msg) {
        std::cerr << "my err handler: " << msg << std::endl;
    });
    logger->set_level(spdlog::level::trace);

    Resources::init();

    std::string a = "res://hello", b = "res://bye", c  = "res://world";
    Resources::parse({&a, &b, &c});
    logger->debug("{}, {}, {}", a, b, c);

    logger->flush();

    Fonts::init();
    Fonts::loadFont("arial", "res://fonts/arial.ttf");

	Shader shader("res://shader/shader.vert", "res://shader/shader.frag");

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glGenVertexArrays(1, &Graphics::VAO);
    glGenBuffers(1, &Graphics::VBO);

    glBindVertexArray(Graphics::VAO);

    glBindBuffer(GL_ARRAY_BUFFER, Graphics::VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    Texture texture1(0, GL_TEXTURE_2D), texture2(1, GL_TEXTURE_2D);
    texture1.load("res://container.jpg", GL_RGB, GL_UNSIGNED_BYTE);
    texture2.load("res://awesomeface.png", GL_RGBA, GL_UNSIGNED_BYTE);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    glUseProgram(shader.id); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    shader.setInt("texture1", texture1.bindToUnit);
    shader.setInt("texture2", texture2.bindToUnit);

    glm::vec3 cubes[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };


    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window))
	{
        Time::update();

        cameraController.processKeyboard(window);

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Fonts::get("arial").render("Text", 25.0f, 25.0f, 1.0f, glm::vec3(0.5f, 0.8f, 0.2f));

        texture1.bind();
        texture2.bind();

        glUseProgram(shader.id);
        int viewLoc = glGetUniformLocation(shader.id, "view");
        int projLoc = glGetUniformLocation(shader.id, "projection");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.getView()));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera.getProjection()));

        glBindVertexArray(Graphics::VAO);
        for(int i = 0; i < 10; i++) {
            glm::mat4 model(1.0f);
            model = glm::translate(model, cubes[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 1.0f, 0.5f));
            int modelLoc = glGetUniformLocation(shader.id, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &Graphics::VAO);
	glDeleteBuffers(1, &Graphics::VBO);

    Fonts::dispose();

	glfwTerminate();
	return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    std::cout << "[Screen] Resize: " << height << "x" << width << std::endl;
    Graphics::screenWidth = width;
    Graphics::screenHeight = height;
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        int mode = glfwGetInputMode(window, GLFW_CURSOR);
        glfwSetInputMode(window, GLFW_CURSOR, mode == GLFW_CURSOR_NORMAL ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    }
}

void mouseCallback(GLFWwindow* window, double x, double y) {
    cameraController.processMouseMove(window, x, y);
}