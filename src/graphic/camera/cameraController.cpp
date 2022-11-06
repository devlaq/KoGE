//
// Created by devla on 2022-11-02.
//

#include "cameraController.h"

void CameraController::processKeyboard(GLFWwindow *window) {
    float velocity = this->moveSpeed * (float)Time::deltaTime;
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->position += camera->front * velocity;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->position -= camera->front * velocity;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->position -= camera->right * velocity;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->position += camera->right * velocity;
}

void CameraController::processMouseMove(GLFWwindow *window, double x, double y) {
    static double lastX = x, lastY = y;

    double xOffset = x - lastX;
    double yOffset = lastY - y;

    lastX = x;
    lastY = y;

    camera->yaw += (float)xOffset * mouseSensitivity;
    camera->pitch += (float)yOffset * mouseSensitivity;

    if(camera->pitch > 89.0f) camera->pitch = 89.0f;
    if(camera->pitch < -89.0f) camera->pitch = -89.0f;

    camera->update();
}

void CameraController::processMouseScroll(GLFWwindow *window, double x, double y) {

}
