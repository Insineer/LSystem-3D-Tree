#pragma once

#include <string>
#include <sstream>
#include <vector>

#include "Graphics/Window.hpp"
#include "Utility/Primitive.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "Graphics/Shader.hpp"

class Tree {
private:
    std::string code;

    float branchSize;
    float size;
    int age;

    float viewAngle;
    float viewRange;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> colors;

    GLuint VAO;
    GLuint VBO;
    GLuint VBOcolors;
    Shader shader;

public:
    Tree();

    void Grow();
    void RotateRight() { viewAngle += 5; }
    void RotateLeft() { viewAngle -= 5; }
    void Closer() { viewRange -= 0.1f; }
    void Father() { viewRange += 0.1f; }

    void Draw();

    const std::string &GetCode() const;
};