//
// Created by Oleki on 16.06.2026.
//
#include "stb_image.h"
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
    glEnable(GL_DEPTH_TEST);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  // window resize callback
    glfwSetCursorPosCallback(window, mouse_callback);                   // mouse coursor callback
    glfwSetWindowUserPointer(window, this);                       // wskaźnik na obecne okno


    // ###### prostokąt ###### //

    // XYZ  Nx, Ny, Nz
    std::vector<float> rectangleVertices = {
        // XYZ(3)             // Normalne(3)
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
         0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,

         0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    glGenVertexArrays(1, &VAO_rect);
    glGenBuffers(1, &VBO_rect);
    glBindVertexArray(VAO_rect);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_rect);
    glBufferData(GL_ARRAY_BUFFER, rectangleVertices.size() * sizeof(float), rectangleVertices.data(), GL_STATIC_DRAW);

    // wierzchołki
    glVertexAttribPointer(0,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)0);
    glEnableVertexAttribArray(0);

    // normalne
    glVertexAttribPointer(1
        , 3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // ###### prostokąt ###### //


    // ###### trójkąt ###### //

    std::vector<float> triangleVertices = {
        // XYZ(3)                 // Normalne(3)
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
         0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    glGenVertexArrays(1, &VAO_tri);
    glGenBuffers(1, &VBO_tri);
    glBindVertexArray(VAO_tri);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_tri);
    glBufferData(GL_ARRAY_BUFFER, triangleVertices.size() * sizeof(float), triangleVertices.data(), GL_STATIC_DRAW);

    // wierzchołki
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)0);
    glEnableVertexAttribArray(0);

    // normalne
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // ###### trójkąt ###### //

    // ###### kula ###### //
    std::vector<float> sphereVertices = generateSphereGeometry(0.5f, 36, 18);
    sphereVertexCount = sphereVertices.size() / 6;
    glGenVertexArrays(1, &VAO_sphere);
    glGenBuffers(1, &VBO_sphere);
    glBindVertexArray(VAO_sphere);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_sphere);
    glBufferData(GL_ARRAY_BUFFER, sphereVertices.size() * sizeof(float), sphereVertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);   // wierzchołki
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // normalne
    glEnableVertexAttribArray(1);
    // ###### kula ###### //

    // ###### cylinder ###### //
    std::vector<float> cylinderVertices = generateCylinderGeometry(0.5f, 1.0f, 36);
    cylinderVertexCount = cylinderVertices.size() / 6;
    glGenVertexArrays(1, &VAO_cylinder);
    glGenBuffers(1, &VBO_cylinder);
    glBindVertexArray(VAO_cylinder);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_cylinder);
    glBufferData(GL_ARRAY_BUFFER, cylinderVertices.size() * sizeof(float), cylinderVertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);   // wierzchołki
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // normalne
    glEnableVertexAttribArray(1);
    // ###### cylinder ###### //

    // ###### stożek ###### //
    std::vector<float> coneVertices = generateConeGeometry(0.5f, 1.0f, 36);
    coneVertexCount = coneVertices.size() / 6;
    glGenVertexArrays(1, &VAO_cone);
    glGenBuffers(1, &VBO_cone);
    glBindVertexArray(VAO_cone);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_cone);
    glBufferData(GL_ARRAY_BUFFER, coneVertices.size() * sizeof(float), coneVertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);   // wierzchołki
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // normalne
    glEnableVertexAttribArray(1);
    // ###### stożek ###### //

    // ###### skybox ###### //
    std::vector<float> skyboxVertices = {
        // back face
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        // front face
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,

         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        // left face
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,

        // right face
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,

         1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,

        // bottom face
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,

         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,

        // top face
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,

         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f
    };
    glGenVertexArrays(1, &VAO_skybox);
    glGenBuffers(1, &VBO_skybox);

    glBindVertexArray(VAO_skybox);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_skybox);

    glBufferData(
        GL_ARRAY_BUFFER,
        skyboxVertices.size() * sizeof(float),
        skyboxVertices.data(),
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0
    );
    glEnableVertexAttribArray(0);
    // ###### skybox ###### //

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

    shader = Shader("vertex.vex", "fragment.frag");  // wczytywanie shaderow
    skyboxShader = Shader("skybox.vex", "skybox.frag"); // wczytywanie shaderow skyboxa

    std::vector<std::string> faces = {
        "../skybox/right.jpg",      // +X
            "../skybox/left.jpg",   // -X
            "../skybox/top.jpg",    // +Y
            "../skybox/bottom.jpg", // -Y
            "../skybox/front.jpg",  // +Z
            "../skybox/back.jpg"    // -Z
    };
    cubemapTexture = loadCubemap(faces);
    skyboxShader.use();
    //skyboxShader.setUniformInt("skybox", 0);

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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // bufor kolorów i bufor głębokości

    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBindVertexArray(VAO);
    shader.use();

    shader.setUniformVec3("lightColor", 1.0f, 1.0f, 1.0f);  // biały ambient light
    shader.setUniformVec3("objectColor", 0.1f, 0.85f, 0.15f); // wszystkie obiekty są 1 barwy
    shader.setUniformVec3("lightPos", 1.0f, 0.0f, 0.0f);    // umiejscowenie źródła światła
    shader.setUniformVec3("viewPos", camera.position.x, camera.position.y, camera.position.z);  // pozycja kamery (specular lighting)


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
    frame.position = glm::vec3(-4 - glm::cos(currentFrame * 1.f) * 1.f, 0.0f, 0.0f);
    frame.yaw = glm::sin(currentFrame * 2.f) * 60.f;
    frame.roll = glm::sin(currentFrame * 5.f) * 45.f;  // animacja obrotu (mnożnik określa maksymalny kąt wychylenia)
    //frame.clamp();
    drawRectangle();

    frame.position = glm::vec3(1.0f, 2.0f, 0.0f);
    frame.roll = 0.0f;
    frame.yaw = currentFrame * 165.0f;
    //frame.clamp();
    drawTriangle();

    frame.position = glm::vec3(0.0f, 0.0f, -2.5f);
    frame.roll = currentFrame * 6.f;
    frame.yaw = currentFrame * 9.f;
    drawCone();

    frame.position = glm::vec3(3.f, 0.0f, 0.0f);
    frame.roll = 0.0f;
    frame.yaw = 0.0f;
    drawCylinder();

    frame.position = glm::vec3(-0.0f, -3.f, -0.0f);
    frame.roll = 0.0f;
    frame.yaw = 0.0f;
    drawSphere();


    // skybox
    glDepthFunc(GL_LEQUAL); // less or equal - 1.0 == 1.0 dla skybox
    skyboxShader.use();
    glm::mat4 viewMatrixSkybox = glm::mat4(glm::mat3(camera.getViewMatrix()));  // usunięcie translacji (pozycji kamery) z macierzy View poprzez translacje(T) macierzy
    //glm::mat4 viewMatrixSkybox = camera.getViewMatrix();
    //glm::mat4 viewMatrixSkybox = glm::scale(glm::mat4(1.0f), glm::vec3(500.0f));

    //Wysłanie macierzy do shadera skyboxa
    skyboxShader.setUniformMat4("view", viewMatrixSkybox);
    skyboxShader.setUniformMat4("projection", projectionMatrix);

    // aktywacja tekstury, bindowanie skyboxa
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);

    // rysowanie
    glBindVertexArray(VAO_skybox);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    glDepthFunc(GL_LESS);   // eless

    // ####### RYSOWANIE ###### //


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

void Renderer::drawSphere() {
    glm::mat4 modelMatrix = frame.getMatrix();
    unsigned int modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glBindVertexArray(VAO_sphere);
    glDrawArrays(GL_TRIANGLES, 0, sphereVertexCount);
}

void Renderer::drawCylinder() {
    glm::mat4 modelMatrix = frame.getMatrix();
    unsigned int modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glBindVertexArray(VAO_cylinder);
    glDrawArrays(GL_TRIANGLES, 0, cylinderVertexCount);
}

void Renderer::drawCone() {
    glm::mat4 modelMatrix = frame.getMatrix();
    unsigned int modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glBindVertexArray(VAO_cone);
    glDrawArrays(GL_TRIANGLES, 0, coneVertexCount);
}

std::vector<float> Renderer::generateSphereGeometry(float radius, int sectorCount, int stackCount) {
    std::vector<float> vertices;
    float x, y, z, xy;
    float nx, ny, nz, lengthInv = 1.0f / radius;
    float sectorStep = 2 * Renderer::M_PI / sectorCount;
    float stackStep = Renderer::M_PI / stackCount;
    float sectorAngle, stackAngle;

    std::vector<float> tempVertices;
    std::vector<float> tempNormals;

    for (int i = 0; i <= stackCount; ++i) {
        stackAngle = Renderer::M_PI / 2 - i * stackStep;
        xy = radius * cosf(stackAngle);
        z = radius * sinf(stackAngle);

        for (int j = 0; j <= sectorCount; ++j) {
            sectorAngle = j * sectorStep;
            x = xy * cosf(sectorAngle);
            y = xy * sinf(sectorAngle);

            tempVertices.push_back(x);
            tempVertices.push_back(y);
            tempVertices.push_back(z);

            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            tempNormals.push_back(nx);
            tempNormals.push_back(ny);
            tempNormals.push_back(nz);
        }
    }

    for (int i = 0; i < stackCount; ++i) {
        int k1 = i * (sectorCount + 1);
        int k2 = k1 + sectorCount + 1;

        for (int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
            if (i != 0) {
                vertices.push_back(tempVertices[k1 * 3]); vertices.push_back(tempVertices[k1 * 3 + 1]); vertices.push_back(tempVertices[k1 * 3 + 2]);
                vertices.push_back(tempNormals[k1 * 3]); vertices.push_back(tempNormals[k1 * 3 + 1]); vertices.push_back(tempNormals[k1 * 3 + 2]);

                vertices.push_back(tempVertices[k2 * 3]); vertices.push_back(tempVertices[k2 * 3 + 1]); vertices.push_back(tempVertices[k2 * 3 + 2]);
                vertices.push_back(tempNormals[k2 * 3]); vertices.push_back(tempNormals[k2 * 3 + 1]); vertices.push_back(tempNormals[k2 * 3 + 2]);

                vertices.push_back(tempVertices[(k1 + 1) * 3]); vertices.push_back(tempVertices[(k1 + 1) * 3 + 1]); vertices.push_back(tempVertices[(k1 + 1) * 3 + 2]);
                vertices.push_back(tempNormals[(k1 + 1) * 3]); vertices.push_back(tempNormals[(k1 + 1) * 3 + 1]); vertices.push_back(tempNormals[(k1 + 1) * 3 + 2]);
            }

            if (i != (stackCount - 1)) {
                vertices.push_back(tempVertices[(k1 + 1) * 3]); vertices.push_back(tempVertices[(k1 + 1) * 3 + 1]); vertices.push_back(tempVertices[(k1 + 1) * 3 + 2]);
                vertices.push_back(tempNormals[(k1 + 1) * 3]); vertices.push_back(tempNormals[(k1 + 1) * 3 + 1]); vertices.push_back(tempNormals[(k1 + 1) * 3 + 2]);

                vertices.push_back(tempVertices[k2 * 3]); vertices.push_back(tempVertices[k2 * 3 + 1]); vertices.push_back(tempVertices[k2 * 3 + 2]);
                vertices.push_back(tempNormals[k2 * 3]); vertices.push_back(tempNormals[k2 * 3 + 1]); vertices.push_back(tempNormals[k2 * 3 + 2]);

                vertices.push_back(tempVertices[(k2 + 1) * 3]); vertices.push_back(tempVertices[(k2 + 1) * 3 + 1]); vertices.push_back(tempVertices[(k2 + 1) * 3 + 2]);
                vertices.push_back(tempNormals[(k2 + 1) * 3]); vertices.push_back(tempNormals[(k2 + 1) * 3 + 1]); vertices.push_back(tempNormals[(k2 + 1) * 3 + 2]);
            }
        }
    }
    return vertices;
}

std::vector<float> Renderer::generateCylinderGeometry(float radius, float height, int sectorCount) {
    std::vector<float> vertices;
    float sectorStep = 2 * Renderer::M_PI / sectorCount;
    float halfHeight = height / 2.0f;

    // Boki
    for (int i = 0; i < sectorCount; ++i) {
        float angle1 = i * sectorStep;
        float angle2 = (i + 1) * sectorStep;

        float x1 = radius * cos(angle1), z1 = radius * sin(angle1);
        float x2 = radius * cos(angle2), z2 = radius * sin(angle2);

        // Normalne dla boku
        float nx1 = cos(angle1), nz1 = sin(angle1);
        float nx2 = cos(angle2), nz2 = sin(angle2);

        // Trójkąt 1
        vertices.insert(vertices.end(), {x1, -halfHeight, z1, nx1, 0.0f, nz1});
        vertices.insert(vertices.end(), {x2, -halfHeight, z2, nx2, 0.0f, nz2});
        vertices.insert(vertices.end(), {x1, halfHeight, z1, nx1, 0.0f, nz1});

        // Trójkąt 2
        vertices.insert(vertices.end(), {x1, halfHeight, z1, nx1, 0.0f, nz1});
        vertices.insert(vertices.end(), {x2, -halfHeight, z2, nx2, 0.0f, nz2});
        vertices.insert(vertices.end(), {x2, halfHeight, z2, nx2, 0.0f, nz2});
    }

    // Podstawy
    for (int i = 0; i < sectorCount; ++i) {
        float angle1 = i * sectorStep;
        float angle2 = (i + 1) * sectorStep;

        float x1 = radius * cos(angle1), z1 = radius * sin(angle1);
        float x2 = radius * cos(angle2), z2 = radius * sin(angle2);

        // Górna (Normalna +Y)
        vertices.insert(vertices.end(), {0.0f, halfHeight, 0.0f, 0.0f, 1.0f, 0.0f});
        vertices.insert(vertices.end(), {x1, halfHeight, z1, 0.0f, 1.0f, 0.0f});
        vertices.insert(vertices.end(), {x2, halfHeight, z2, 0.0f, 1.0f, 0.0f});

        // Dolna (Normalna -Y)
        vertices.insert(vertices.end(), {0.0f, -halfHeight, 0.0f, 0.0f, -1.0f, 0.0f});
        vertices.insert(vertices.end(), {x2, -halfHeight, z2, 0.0f, -1.0f, 0.0f});
        vertices.insert(vertices.end(), {x1, -halfHeight, z1, 0.0f, -1.0f, 0.0f});
    }

    return vertices;
}

std::vector<float> Renderer::generateConeGeometry(float radius, float height, int sectorCount) {
    std::vector<float> vertices;
    float sectorStep = 2 * Renderer::M_PI / sectorCount;
    float halfHeight = height / 2.0f;

    // Normalna ściany
    float ny = radius / sqrt(radius*radius + height*height);

    for (int i = 0; i < sectorCount; ++i) {
        float angle1 = i * sectorStep;
        float angle2 = (i + 1) * sectorStep;

        float x1 = radius * cos(angle1), z1 = radius * sin(angle1);
        float x2 = radius * cos(angle2), z2 = radius * sin(angle2);

        float nx1 = cos(angle1), nz1 = sin(angle1);
        float nx2 = cos(angle2), nz2 = sin(angle2);

        float nx_avg = (nx1 + nx2) / 2.0f;
        float nz_avg = (nz1 + nz2) / 2.0f;

        // Bok (trójkąt od podstawy do wierzchołka)
        vertices.insert(vertices.end(), {x1, -halfHeight, z1, nx1, ny, nz1});
        vertices.insert(vertices.end(), {x2, -halfHeight, z2, nx2, ny, nz2});
        vertices.insert(vertices.end(), {0.0f, halfHeight, 0.0f, nx_avg, ny, nz_avg}); // Szczyt

        // Podstawa (Normalna -Y)
        vertices.insert(vertices.end(), {0.0f, -halfHeight, 0.0f, 0.0f, -1.0f, 0.0f});
        vertices.insert(vertices.end(), {x2, -halfHeight, z2, 0.0f, -1.0f, 0.0f});
        vertices.insert(vertices.end(), {x1, -halfHeight, z1, 0.0f, -1.0f, 0.0f});
    }

    return vertices;
}

unsigned int Renderer::loadTexture(char const* path) {
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, channelsInFile;   // ilość kanalów
    stbi_set_flip_vertically_on_load(true);     // tekstury mają Y w lewym górnym rogu - openGL w lewym dolnym

    unsigned char *data = stbi_load(path, &width, &height, &channelsInFile, 0);
    if (data) {
        GLenum format;
        if (channelsInFile == 1) format = GL_RED;
        else if (channelsInFile == 3) format = GL_RGB;
        else if (channelsInFile == 4) format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);   // wyslanie obrazu do GPU
        glGenerateMipmap(GL_TEXTURE_2D);    // generowanie mipmap

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   // repeat w osi X
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);   // repeat w osi Y
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        std::cout << "Błąd przy wczytywaniu tekstury: " << path << "\n";
        stbi_image_free(data);
    }
    return textureID;
}

unsigned int Renderer::loadCubemap(std::vector<std::string> faces) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(false);

    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); // wyslanie obrazu do GPU
            stbi_image_free(data);
        } else {
            std::cout << "Błąd przy wczytywaniu tekstury cubemapy: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }

    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS); // wygładzanie szwów cubemapy
    // Minification Filter (filtr pomniejszania)
    // gl_linear - usrednienienie na podstawie sasiadow
    // gl_nearest - najblizszy sasiad
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // wygładza krawędzie pikseli, gdy podchodzimy blisko ściany

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // blokuje współrzędną na krawędzi w osi X, zamiast ją powtarzać
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // blokuje współrzędną na krawędzi w osi Y, zamiast ją powtarzać
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE); // blokuje współrzędną na krawędzi w osi Z, zamiast ją powtarzać

    return textureID;
}