//
// Created by devla on 2022-11-02.
//

#ifndef KORPG_CAMERACONTROLLER_H
#define KORPG_CAMERACONTROLLER_H

#include <GLFW/glfw3.h>

#include "camera.h"
#include "../../time.h"

class CameraController {
private:
    Camera* camera;
public:
    float moveSpeed;
    float mouseSensitivity;

    explicit CameraController(Camera* camera, float moveSpeed = 2.5f, float mouseSensitivity = 0.1f) {
        this->camera = camera;
        this->moveSpeed = moveSpeed;
        this->mouseSensitivity = mouseSensitivity;
    }

    void processKeyboard(GLFWwindow* window);
    void processMouseMove(GLFWwindow* window, double x, double y);
    void processMouseScroll(GLFWwindow* window, double x, double y);
};


#endif //KORPG_CAMERACONTROLLER_H
