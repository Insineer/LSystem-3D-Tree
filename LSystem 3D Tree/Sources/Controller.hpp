#pragma once

#include "Utility/Pointer.hpp"
#include "Tree.hpp"
#include "Graphics/Window.hpp"

class Controller {
private:
    uptr<Tree> tree;
    uptr<Window> window;

    static Controller *inst;

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

public:
    Controller();

    static Controller &Get();
    Window *GetWindow() { return window.get(); }
};