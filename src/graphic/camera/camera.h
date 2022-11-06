//
// Created by devla on 2022-11-02.
//

#ifndef KORPG_CAMERA_H
#define KORPG_CAMERA_H

#include "glm/glm.hpp"

struct Camera {
public:
    glm::vec3 position, front, up, right, worldUp;
    float yaw, pitch;

    virtual glm::mat4 getView() = 0;
    virtual glm::mat4 getProjection() = 0;
    virtual void update() = 0;
};


#endif //KORPG_CAMERA_H
