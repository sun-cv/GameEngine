#pragma once

#include "CoreUtility.h"
#include "ForwardEvent.h"
#include "RenderGladGLFW.h"

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

        void shutdown();

        GLFWwindow* getWindow() { return window; };
};
