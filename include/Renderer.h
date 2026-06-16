//
// Created by Oleki on 16.06.2026.
//

#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "Shader.h"

class Renderer {
public:
    GLFWwindow* window;
    Shader shader;
    Camera camera;
    // unsigned int VBO;   // Vertex Buffer Object
    // unsigned int VAO;   // Vertex Array Object

    Frame frame;

    unsigned int VAO_rect, VBO_rect;
    unsigned int VAO_tri, VBO_tri;

    float lastFrame = 0;


    std::vector<float> vertices = {
        -0.9f, -0.2f, // Lewy dolny róg
        -0.5f,  0.5f, // Górny róg
        -0.1f, -0.2f, // Prawy dolny róg

         0.1f, -0.2f, // Lewy dolny róg
         0.5f,  0.5f, // Górny róg
         0.9f, -0.2f  // Prawy dolny róg
    };

    bool mouseCaptured = true;
    bool isTerminated = false;

    Renderer() {}
    void init();
    void render();

    void drawRectangle();
    void drawTriangle();

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);  // callback gdy jest zmienany rozmiar okna
    static void mouse_callback(GLFWwindow* window, double x, double y);                  // callback gdy mysz się poruszyła
};



#endif //RENDERER_H
