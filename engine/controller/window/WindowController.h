#ifndef WINDOW_CONTROLLER_H
#define WINDOW_CONTROLLER_H

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "CoreEngine.h"
#include "CoreEvent.h"
#include "CoreRender.h"



class WindowController
{
    private:
        const char *title                       = "Game Engine";
        GLFWwindow *window;
    
    public:
        int width                               = 1280;
        int height                              = 720; 

    private:
        static void framebuffer_size_callback   (GLFWwindow* window, int width, int height);
        static void window_size_callback        (GLFWwindow* window, int width, int height);
        static void window_refresh_callback     (GLFWwindow* window);
        
        void registerListeners();
        void closeWindow                        (Event& event);

    public:
        WindowController();
        ~WindowController();

        void initialize();
        bool active();

        void pollEvents();
        void windowRefresh();
        void clear();
        void swapBuffers();

        void terminate();

        GLFWwindow* getWindow() { return window; };
};



#endif;