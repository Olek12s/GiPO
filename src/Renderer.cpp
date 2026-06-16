//
// Created by Oleki on 16.06.2026.
//

#include "../include/Renderer.h"

void Renderer::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // wersja major GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  // wersja minor GLFW
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // use core profile GLFW

    window = glfwCreateWindow(800, 600, "GIPO", nullptr, nullptr);    // init obiektu window
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);    // mouse ENABLE

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))    // load openGL function pointers
    {
        std::cout << "Failed to initialize GL Loader-Generator (GLAD)" << std::endl;
        return;
    }

    //glfwSwapInterval(0);    // 0 = VSync Off
    glViewport(0, 0, 800, 600); // obszar view-Port

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  // window resize callback
    glfwSetCursorPosCallback(window, mouse_callback);                   // mouse coursor callback
    glfwSetWindowUserPointer(window, this);                       // wskaźnik na obecne okno


    std::vector<float> rectangleVertices = { // kształt 2D: XY XY XY XY XY XY
        -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f,
         0.5f,  0.5f, -0.5f, 0.5f, -0.5f, -0.5f
    };
    glGenVertexArrays(1, &VAO_rect);
    glGenBuffers(1, &VBO_rect);
    glBindVertexArray(VAO_rect);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_rect);
    glBufferData(GL_ARRAY_BUFFER, rectangleVertices.size() * sizeof(float), rectangleVertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0,
        2,
        GL_FLOAT,
        GL_FALSE,
        2 * sizeof(float),
        (void*)0);
    glEnableVertexAttribArray(0);


    std::vector<float> triangleVertices = { // kształt 2D: XY XY XY
        -0.5f, -0.5f,   0.5f, -0.5f,   0.0f,  0.5f
    };
    glGenVertexArrays(1, &VAO_tri);
    glGenBuffers(1, &VBO_tri);
    glBindVertexArray(VAO_tri);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_tri);
    glBufferData(GL_ARRAY_BUFFER, triangleVertices.size() * sizeof(float), triangleVertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // VAO
    // glGenVertexArrays(1, &VAO);
    // glBindVertexArray(VAO); // aktywacja VAO
    //
    // glGenBuffers(1, &VBO);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO); // aktywacja VBO
    //
    // // wysyłanie danych vertices do GPU
    // glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // jak czytać VBO
    // glVertexAttribPointer(
    //     0,                              // index - atrybut w shaderze
    //     2,                              // size - ile składowych ma 1 vertex
    //     GL_FLOAT,                       // type - typ
    //     GL_FALSE,                       // normalized
    //     2 * sizeof(float),               // stride - liczba bajtów na 1 vertex
    //     (void*)(0)                      // offset
    // );
    // glEnableVertexAttribArray(0);

    shader = Shader("Particle.vex", "Particle.frag");  // wczytywanie shaderow
    shader.use();
}

void Renderer::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
    glViewport(0, 0, width, height);
}

void Renderer::mouse_callback(GLFWwindow* window, double x, double y)
{
    Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
    renderer->camera.mouseInput((float)x, (float)y);
}

void Renderer::render() {
    if (glfwWindowShouldClose(window)) {
        isTerminated = true;
        return;
    }

    float currentFrame = glfwGetTime();
    float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    camera.update(window, deltaTime);   // klawiatura

    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBindVertexArray(VAO);
    shader.use();

    //glm::mat4 modelMatrix(1.0f);    // macierz jednostkowa
    glm::mat4 viewMatrix = camera.getViewMatrix();
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(Camera::fov), 800.0f / 600.0f, 0.1f, 1000.0f);

    //unsigned int model = glGetUniformLocation(shader.ID, "model");
    unsigned int view = glGetUniformLocation(shader.ID, "view");
    unsigned int projection = glGetUniformLocation(shader.ID, "projection");

    // wysyłanie do GPU model i view
    //glUniformMatrix4fv(model,1,GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(view,1,GL_FALSE,glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));


    // ####### RYSOWANIE ###### //
    //frame.position = glm::vec3(-1.0f, 0.0f, 0.0f);
    frame.position = glm::vec3(-1 - glm::cos(currentFrame * 1.f) * 1.f, 0.0f, 0.0f);
    frame.yaw = 0.0f;
    frame.roll = glm::sin(currentFrame * 5.f) * 45.f;  // animacja obrotu (mnożnik określa maksymalny kąt wychylenia)
    frame.clamp();
    drawRectangle();

    frame.position = glm::vec3(1.0f, 0.0f, 0.0f);
    frame.roll = 0.0f;
    frame.yaw = currentFrame * 165.0f;
    frame.clamp();
    drawTriangle();

    // ####### RYSOWANIE ###### //


    // renderuj trójkąty na podstawie określonego glVertexAttribPointer(...)
    //glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 2);

    glfwSwapBuffers(window);   // double buffer
    glfwPollEvents();   // wydarzenia / eventy
}

void Renderer::drawRectangle() {
    // Pobieramy macierz modelu z frame i wysyłamy do GPU
    glm::mat4 modelMatrix = frame.getMatrix();
    unsigned int modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // przełączamy się na wierzchołki tego obiektu
    glBindVertexArray(VAO_rect);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::drawTriangle() {
    // Pobieramy macierz modelu z frame i wysyłamy do GPU
    glm::mat4 modelMatrix = frame.getMatrix();
    unsigned int modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // przełączamy się na wierzchołki tego obiektu
    glBindVertexArray(VAO_tri);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
