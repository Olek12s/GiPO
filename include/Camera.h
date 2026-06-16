//
// Created by Oleki on 16.06.2026.
//

#ifndef CAMERA_H
#define CAMERA_H
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Frame.h"

class Camera {
public:
    // Pozycja i kierunki
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    // Kąty Eulera
    float yaw;
    float pitch;

    // Opcje myszy i kamery
    float lastX;
    float lastY;
    bool firstMouse;
    float speed;
    float sensitivity;

    // field of fiev
    static inline float fov = 45.f;

    Camera();
    void update(GLFWwindow* window, float deltaTime);
    void keyboardInput(GLFWwindow *window, float deltaTime);
    void mouseInput(float xpos, float ypos);
    glm::mat4 getViewMatrix();
    void updateCameraVectors();
};



#endif //CAMERA_H
