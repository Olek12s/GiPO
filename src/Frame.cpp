//
// Created by Oleki on 16.06.2026.
//

#include "../include/Frame.h"
#include <glm/glm.hpp>
#include "glm/detail/type_mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

void Frame::clamp() {
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    if (yaw > 360.0f) yaw -= 360.0f;
    if (yaw < 0.0f) yaw += 360.0f;

    if (roll > 180.0f) roll -= 180.0f;
    if (roll < -180.0f) roll += -180.0f;
}

glm::mat4 Frame::getMatrix() {
    glm::mat4 matrix(1.0f); // macierz jednostkowa

    matrix = glm::translate(matrix, position);

    matrix = glm::rotate(matrix,glm::radians(yaw),glm::vec3(0.0f, 1.0f, 0.0f));     // y
    matrix = glm::rotate(matrix,glm::radians(pitch),glm::vec3(1.0f, 0.0f, 0.0f));   // x
    matrix = glm::rotate(matrix,glm::radians(roll),glm::vec3(0.0f, 0.0f, 1.0f));    // z

    return matrix;
}

