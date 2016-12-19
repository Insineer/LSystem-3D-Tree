#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class Shader {
private:
    GLuint program;

public:
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    void Use();

    GLuint GetProgram() const { return program; }
};