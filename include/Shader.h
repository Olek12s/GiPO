//
// Created by Oleki on 16.06.2026.
//

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <iostream>
#include <fstream>

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

class Shader {
public:
unsigned int ID;

    Shader() {}

    Shader(const std::string& shaderVex, const std::string& shaderFrag) {

        // ##### wczytywanie z pliku ##### //
        std::ifstream vexFile("../shaders/" + shaderVex);
        std::ifstream fragFile("../shaders/" + shaderFrag);

        bool loadFail = false;
        if (!vexFile.is_open()) {
            std::cout << "Failed to read vertex shader file: " << shaderVex << "\n";
            loadFail = true;
        }

        if (!fragFile.is_open()) {
            std::cout << "Failed to read fragment shader file: " << shaderFrag << "\n";
            loadFail = true;
        }
        if (loadFail) return;

        std::string vexCode;
        std::string fragCode;
        std::string line;

        while (std::getline(vexFile, line)) {
            vexCode.append(line);
            vexCode.append("\n");
        }

        while (std::getline(fragFile, line)) {
            fragCode.append(line);
            fragCode.append("\n");
        }

        vexFile.close();
        fragFile.close();

        std::cout << "Vertex shader loaded (" << vexCode.size() << " bytes)\n";
        std::cout << "Fragment shader loaded (" << fragCode.size() << " bytes)\n";
        // ##### wczytywanie z pliku ##### //



        // ##### kompilacja shaderów ##### //
        unsigned int vexID;
        int ok;
        char logs[1024];
        const char* srcVex = vexCode.c_str();
        const char* srcFrag = fragCode.c_str();

        vexID = glCreateShader(GL_VERTEX_SHADER);               // tworzenie obiektu
        glShaderSource(vexID, 1, &srcVex, nullptr);      // wstawianie kodu do shadera z określonym ID
        glCompileShader(vexID);                                      // kompilacja shadera
        glGetShaderiv(vexID, GL_COMPILE_STATUS, &ok);    // weryfikacja kompilacji

        if (!ok) {
            glGetShaderInfoLog(vexID, 1024, nullptr, logs);
            std::cout << "Failed to compile Vertex Shaders: " << logs << "\n";
        }

        unsigned int fragID;
        fragID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragID, 1, &srcFrag, nullptr);
        glCompileShader(fragID);
        glGetShaderiv(fragID, GL_COMPILE_STATUS, &ok);

        if (!ok) {
            glGetShaderInfoLog(fragID, 1024, nullptr, logs);
            std::cout << "Failed to compiled Fragment Shaders: " << logs << "\n";
            return;
        }
        // ##### kompilacja shaderów ##### //


        // ##### Tworzenie programu shadera ##### //
        ID = glCreateProgram();
        glAttachShader(ID, vexID);
        glAttachShader(ID, fragID);
        glLinkProgram(ID);

        glGetProgramiv(ID, GL_LINK_STATUS, &ok);
        if (!ok) {
            glGetProgramInfoLog(ID, 1024, nullptr, logs);
            std::cout << "Failed to link shaders: " << logs << "\n";
            return;
        }

        glDeleteShader(vexID);
        glDeleteShader(fragID);
        // ##### Tworzenie programu shadera ##### //

        std::cout << "\n########################################\n";
        std::cout << "Shaders building ended successfully.\n";
        std::cout << "########################################\n\n";
    }

    void use() {
        glUseProgram(ID);
    }

    void setUniformBool(const std::string& name, bool value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }

    void setUniformInt(const std::string& name, int value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setUniformFloat(const std::string& name, float value) const {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setUniformMat3(const std::string& name, const glm::mat4 &mat) const {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
    }

    void setUniformMat4(const std::string& name, const glm::mat4 &mat) const {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
    }

    void setUniformVec3(const std::string& name, float x, float y, float z) const {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }
};



#endif //SHADER_H
