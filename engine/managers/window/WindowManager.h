#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "EngineCore.h"

class WindowManager {
   private:
    const char *title = "Game Engine";
    GLFWwindow *window;

   public:
    WindowManager();
    ~WindowManager();

    int width = 800;
    int height = 600;
    bool initialize();

    void windowRefresh();

    void pollEvents();

    void clear(float r, float g, float b, float a);

    void swapBuffers();

    bool active() const;

    void terminate();
};

#endif