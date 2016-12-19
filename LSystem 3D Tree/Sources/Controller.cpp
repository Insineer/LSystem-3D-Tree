#include <iostream>

#include "Controller.hpp"
#include "Graphics/Shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Controller::Controller() {
    inst = this;
    window.reset(new Window(1200, 900));

    glfwSetKeyCallback(window->GetGLFWWindow(), key_callback);

    tree.reset(new Tree());

    Shader shader("Sources/Graphics/shaders/shader.vert", "Sources/Graphics/shaders/shader.frag");

    while (window->IsActive()) {
        window->ProcessEvents();
        window->BeginDrawing();

        tree->Draw();

        window->EndDrawing();
    }
}

void Controller::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (action == GLFW_PRESS)
        switch (key) {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, GL_TRUE);
                break;
            case GLFW_KEY_SPACE:
                inst->tree->Grow();
                break;
        }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) inst->tree->RotateLeft();
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) inst->tree->RotateRight();
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) inst->tree->Closer();
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) inst->tree->Father();
}

Controller &Controller::Get() { return *inst; }
Controller *Controller::inst;