#pragma once

#include "CoreUtility.h"
#include "WindowController.h"
#include "ForwardEvent.h"

// REWORK REQUIRED

class InputController
{   // Variables
    private: // Dependencies
        std::shared_ptr<WindowController>       windowController;

    // Functions
    private:
        void registerListeners                  ();
        void registerCallbacks                  ();
        void createInputEvents                  (Event& event);

        static void keyCallback                 (GLFWwindow* window, int key, int scancode, int action, int mods);
        static void mouseCallback               (GLFWwindow* window, int button, int action, int mods);
        static void mouseScrollCallback         (GLFWwindow* window, double xoffset, double yoffset);
        static void cursorPositionCallback      (GLFWwindow* window, double xpos, double ypos);

        void onKey                              (int key, int scancode, int action, int mods);
        void onMouse                            (int button, int action, int mods);
        void onScroll                           (double xoffset, double yoffset);
        void onMove                             (double xpos, double ypos);

        void handleKeyPress                     (KeyPressedEvent& event);
        void handleKeyRelease                   (KeyReleasedEvent& event);
        void handleKeyRepeat                    (KeyRepeatedEvent& event);

        void handleMouseClick                   (MouseEvent& event);
        void handleMouseScroll                  (MouseScrolledEvent& event);
        void handleMouseMoved                   (MouseMovedEvent& event);

    public:
        InputController                          (std::shared_ptr<WindowController> windowController);
        ~InputController                         ();

};