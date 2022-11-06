//
// Created by devla on 2022-11-02.
//

#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

#include "camera.h"

const float DEFAULT_YAW = -90.0f;
const float DEFAULT_PITCH = 0.0f;
const float DEFAULT_FOV = 45.0f;

class PerspectiveCamera : public Camera {

public:
    float fieldOfView;

    explicit PerspectiveCamera(
            glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
            float yaw = DEFAULT_YAW,
            float pitch = DEFAULT_PITCH,
            float fieldOfView = DEFAULT_FOV
    ) {
        this->position = position;
        this->worldUp = up;
        this->yaw = yaw;
        this->pitch = pitch;
        this->fieldOfView = fieldOfView;
        _update();
    }

    glm::mat4 getView() override {
        glm::mat4 view = glm::lookAt(position, position + front, up);
        return view;
    }

    glm::mat4 getProjection() override {
        int width, height;
        glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);

        glm::mat4 projection = glm::perspective(glm::radians(fieldOfView), (float)width / (float)height, 0.1f, 100.0f);
        return projection;
    }

    void _update() {
        this->update();
    }

    void update() override {
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        this->front = glm::normalize(front);
        this->right = glm::normalize(glm::cross(this->front, this->worldUp));
        this->up    = glm::normalize(glm::cross(this->right, this->front));
    }

};