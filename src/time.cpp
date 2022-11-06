//
// Created by devla on 2022-11-02.
//

#include "./time.h"

double Time::deltaTime;

void Time::update() {
    // Update deltaTime
    static double lastFrame = 0;
    deltaTime = glfwGetTime() - lastFrame;
    lastFrame = glfwGetTime();
}