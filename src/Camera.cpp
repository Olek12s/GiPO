//
// Created by Oleki on 16.06.2026.
//

#include "Camera.h"

Camera::Camera() {
    position = glm::vec3(0.0f, 0.0f, 0.0f); // (0,0,0 środek ekranu)
    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);  // Globalna oś Y
    yaw = -90.0f; // Zwrot w stronę -Z
    pitch = 0.0f;
    front = glm::vec3(0.0f, 0.0f, -1.0f);

    speed = 1.5f;
    sensitivity = 0.1f;
    firstMouse = true;
    lastX = 800.0f / 2.0f;
    lastY = 600.0f / 2.0f;

    updateCameraVectors();
}

void Camera::update(GLFWwindow *window, float deltaTime) {
    keyboardInput(window, deltaTime);
}

void Camera::keyboardInput(GLFWwindow *window, float deltaTime) {
    float velocity = speed * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        position += front * velocity;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        position -= front * velocity;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        position -= right * velocity;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        position += right * velocity;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        position += -up * velocity;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        position += up * velocity;
    }
}

void Camera::mouseInput(float xPos, float yPos) {
    if (firstMouse) {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    // offset pomiędzy ostatnią i obecną klatką
    float xoffset = xPos - lastX;
    float yoffset = lastY - yPos;
    lastX = xPos;
    lastY = yPos;


    xoffset *= sensitivity;
    yoffset *= sensitivity;
    yaw += xoffset;   // Poziomy ruch obraca wokół globalnej osi Y (odchylenie)
    pitch += yoffset; // Pionowy ruch obraca wokół lokalnej osi X kamery (pochylenie)

    // ochrona przeciw przekręceniu kamery
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    updateCameraVectors();
}

void Camera::updateCameraVectors() {
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);

    // Przeliczenie osi lokalnych
    right = glm::normalize(glm::cross(front, worldUp));  // Prawa oś lokalna
    up = glm::normalize(glm::cross(right, front));    // Górna oś lokalna
}



glm::mat4 Camera::getViewMatrix() {
    // przesunięcie całego świata w kierunku odwrotnym do pozycji kamery
    //return glm::translate(glm::mat4(1.0f), glm::vec3(-position.x, -position.y, 0.0f));
    return glm::lookAt(position, position + front, up);
}


