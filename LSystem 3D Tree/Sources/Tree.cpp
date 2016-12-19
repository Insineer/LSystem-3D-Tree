#include "Tree.hpp"

#include <iostream>
#include <stack>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/random.hpp>
#include <glm/glm.hpp>

#include "Controller.hpp"

Tree::Tree() : shader("Sources/Graphics/shaders/shader.vert", "Sources/Graphics/shaders/shader.frag") {
    code = "X";
    branchSize = 0.5;
    viewAngle = 0;
    viewRange = 3;
    age = 0;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glGenBuffers(1, &VBOcolors);
    glBindBuffer(GL_ARRAY_BUFFER, VBOcolors);

    glBindVertexArray(0);
}

void Tree::Grow() {
    if (age >= 20) {
        std::cout << "Maximum age of the tree reached!" << std::endl;
        return;
    }
    age++;
    std::cout << "Tree age: " << age << std::endl;

    std::stringstream sstream;
    for (char &c : code) {
        switch (c) {
            /*case 'F':
                sstream << "FF";
                break;*/
            case 'X':
                sstream << "F[@[-X]+X]";
                break;
            default:
                sstream << c;
        }
    }
    code = sstream.str();

    vertices.clear();
    colors.clear();
    glm::vec3 curPos, curVect, curColor;
    curPos.x = curPos.y = 0;
    curPos.z = 0;
    curVect.x = 0;
    curVect.z = 0;
    curVect.y = branchSize;

    curColor.x = 0;
    curColor.y = 0;
    curColor.z = 0;

    std::stack<glm::vec3> savedPos;
    std::stack<glm::vec3> savedVect;
    std::stack<glm::vec3> savedColor;

    size = 0;

    for (char &c : code) {
        switch (c) {
            case 'F': {
                vertices.push_back(curPos);
                curPos += curVect;
                vertices.push_back(curPos);
                colors.push_back(curColor);
                colors.push_back(curColor);
                if (curPos.y > size) size = curPos.y;
                break;
            }
            case '@': {
                curVect *= 0.95;
                curColor.y += (1 - curColor.y) * 0.05f;
                break;
            }
            case '+':
                curVect = glm::rotateZ(curVect, glm::radians(glm::linearRand<float>(-30.0f, 30.0f)));
                curVect = glm::rotateY(curVect, glm::radians(glm::linearRand<float>(0.0f, 45.0f)));
                break;
            case '-':
                curVect = glm::rotateZ(curVect, glm::radians(glm::linearRand<float>(-30.0f, 30.0f)));
                curVect = glm::rotateY(curVect, glm::radians(glm::linearRand<float>(-45.0f, 0.0f)));
                break;
            case '[':
                savedPos.push(curPos);
                savedVect.push(curVect);
                savedColor.push(curColor);
                break;
            case ']':
                curPos = savedPos.top();
                savedPos.pop();
                curVect = savedVect.top();
                savedVect.pop();
                curColor = savedColor.top();
                savedColor.pop();
                break;
        }
    }

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBOcolors);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * colors.size(), colors.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Tree::Draw() {
    float scale = size > 1.9f ? 1.9f / size : 1.9f;

    glm::mat4 model;
    model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(scale, scale, scale));
    model = glm::rotate(model, glm::radians(viewAngle), glm::vec3(0.0f, 1.0f, 0.0f));
    GLuint modelLoc = glGetUniformLocation(shader.GetProgram(), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glm::mat4 view;
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -viewRange));
    GLuint viewLoc = glGetUniformLocation(shader.GetProgram(), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), float(Controller::Get().GetWindow()->Width()) / Controller::Get().GetWindow()->Height(), 0.1f, 100.0f);
    GLuint projectionLoc = glGetUniformLocation(shader.GetProgram(), "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    shader.Use();
    glBindVertexArray(VAO);

    glDrawArrays(GL_LINES, 0, GLsizei(vertices.size()));

    glBindVertexArray(0);
}

const std::string &Tree::GetCode() const { return code; }