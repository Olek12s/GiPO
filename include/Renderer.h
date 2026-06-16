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
    Shader skyboxShader;
    unsigned int cubemapTexture;
    Camera camera;
    // unsigned int VBO;   // Vertex Buffer Object
    // unsigned int VAO;   // Vertex Array Object

    Frame frame;
    unsigned int VAO_tri, VAO_rect, VAO_sphere, VAO_cylinder, VAO_cone, VAO_skybox;
    unsigned int VBO_tri, VBO_rect, VBO_sphere, VBO_cylinder, VBO_cone, VBO_skybox;

    float lastFrame = 0;
    inline static float M_PI = 3.14159;


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
    void drawCylinder();
    void drawCone();
    void drawSphere();

    std::vector<float> generateSphereGeometry(float radius, int sectorCount, int stackCount);   // kula - sectorCount - liczba trójkątów w podstawie
    std::vector<float> generateCylinderGeometry(float radius, float height, int sectorCount);   // cylinder
    std::vector<float> generateConeGeometry(float radius, float height, int sectorCount);       // stożek

    unsigned int loadTexture(char const* path);                  // tekstura 2D
    unsigned int loadCubemap(std::vector<std::string> faces);   // tekstura cubemap

    int sphereVertexCount;
    int cylinderVertexCount;
    int coneVertexCount;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);  // callback gdy jest zmienany rozmiar okna
    static void mouse_callback(GLFWwindow* window, double x, double y);                  // callback gdy mysz się poruszyła
};



#endif //RENDERER_H
