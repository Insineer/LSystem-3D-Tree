#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Utility/Pointer.hpp"

#include "Tree.hpp"

class Window {
private:
    int width, height;
    bool active;

    GLFWwindow *glfwWindow;

public:
    Window(const int width, const int height);
    ~Window();

    void ProcessEvents();
    void BeginDrawing();
    void EndDrawing();

    bool IsActive() const;
    int Width() const;
    int Height() const;
    GLFWwindow *GetGLFWWindow() const;
};