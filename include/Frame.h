//
// Created by Oleki on 16.06.2026.
//

#ifndef FRAME_H
#define FRAME_H
#include "glm/detail/type_mat.hpp"
#include "glm/detail/type_vec.hpp"
#include "glm/detail/type_vec3.hpp"


class Frame {
public:
    glm::vec3 position;

    float pitch; // "kąt góra dół"
    float yaw;; // "kąt lewo prawo"
    float roll; // "kąt obrotowy"

    Frame() : position(0,0,0), pitch(0), yaw(0), roll(0) {}

    void clamp();
    glm::mat4 getMatrix();
};

#endif //FRAME_H
