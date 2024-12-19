#ifndef WINDOW_CONTROLLER_H
#define WINDOW_CONTROLLER_h

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "EngineCore.h"
#include "EventCore.h"
#include "InputController.h"


class WindowController
{
    private:

        const char *title                       = "Game Engine";
        GLFWwindow *window;

        static void framebuffer_size_callback   (GLFWwindow* window, int width, int height);
        static void window_size_callback        (GLFWwindow* window, int width, int height);
        static void window_refresh_callback     (GLFWwindow* window);
        static void keyCallback                 (GLFWwindow* window, int key, int scancode, int action, int mods);
        static void mouseCallback               (GLFWwindow* window, int button, int action, int mods);
        static void mouseScrollCallback         (GLFWwindow* window, double xoffset, double yoffset);
        static void cursorPositionCallback      (GLFWwindow* window, double xpos, double ypos);

        void onKey                              (int key, int scancode, int action, int mods);
        void onMouse                            (int button, int action, int mods);
        void onScroll                           (double xoffset, double yoffset);
        void onMove                             (double xpos, double ypos);
        
        void createListeners();
        void closeWindow                        (Event& event);

    public:
    
        int width                               = 1280;
        int height                              = 720; 



        WindowController();
        ~WindowController();

        bool initialize();
        bool active();

        void pollEvents();
        void windowRefresh();
        void clear();
        void swapBuffers();

        void terminate();

};



#endif;