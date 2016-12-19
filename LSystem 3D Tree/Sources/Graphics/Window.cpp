#include "Window.hpp"

#include <iostream>

Window::Window(const int width, const int height) : width(width), height(height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    glfwWindow = glfwCreateWindow(width, height, "LSystem 3D Tree", nullptr, nullptr);
    if (glfwWindow == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        active = false;
        return;
    }
    glfwMakeContextCurrent(glfwWindow);
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        active = false;
        return;
    }
    active = true;
}

Window::~Window() {
    glfwTerminate();
}

void Window::ProcessEvents() {
    glfwPollEvents();
    if (glfwWindowShouldClose(glfwWindow)) active = false;
}

void Window::BeginDrawing() {
    glClearColor(230.0f / 255, 230.0f / 255, 250.0f / 255, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::EndDrawing() {
    glfwSwapBuffers(glfwWindow);
}

bool Window::IsActive() const { return active; }
int Window::Width() const { return width; }
int Window::Height() const { return height; }
GLFWwindow *Window::GetGLFWWindow() const { return glfwWindow; }