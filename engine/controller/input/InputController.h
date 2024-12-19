#ifndef INPUT_CONTROLLER_H
#define INPUT_CONTROLLER_H

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "EngineCore.h"
#include "EventCore.h"

class InputController
{
private:
public:
    InputController         ();
    ~InputController        ();

    void createInputEvents  (Event& event);

    void handleKeyPress     (KeyPressedEvent& event);
    void handleKeyRelease   (KeyReleasedEvent& event);
    void handleKeyRepeat    (KeyRepeatedEvent& event);

    void handleMouseClick   (MouseEvent& event);
    void handleMouseScroll  (MouseScrolledEvent& event);
    void handleMouseMoved   (MouseMovedEvent& event);


    void createListeners    ();

};

#endif