#include "InputController.h"

#include "CoreEvent.h"
#include "RenderGladGLFW.h"

InputController::InputController(std::shared_ptr<WindowController> windowController) : windowController(windowController)
{
    LogStartup(Log::cInput); 
    try
    {    
        registerListeners();
        registerCallbacks();
    }
    catch(Exceptions)
    {
        LogFailure(Log::cInput, error);
    }
    LogSuccess(Log::cInput);
}


InputController::~InputController()
{
}
    // Throw
void InputController::registerListeners()
{
    Listener_(EventType::InputEvent,    std::bind(&InputController::createInputEvents, this, std::placeholders::_1));
    Listener_(EventType::MouseScrolled, std::bind(&InputController::createInputEvents, this, std::placeholders::_1));
    Listener_(EventType::MouseMoved,    std::bind(&InputController::createInputEvents, this, std::placeholders::_1));
}

void InputController::registerCallbacks()
{
    GLFWwindow *window = windowController->getWindow(); 

    glfwSetKeyCallback          (window, keyCallback);
    glfwSetMouseButtonCallback  (window, mouseCallback);
    glfwSetScrollCallback       (window, mouseScrollCallback);

    // Enable to track cursor position
    // glfwSetCursorPosCallback (window, cursorPositionCallback);

    Log(Log::System, Log::cInput, "Registered input callbacks");
}


void InputController::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    InputController* controller = static_cast<InputController*>(glfwGetWindowUserPointer(window));
    if (!controller)
    {
        return;
    }
    controller->onKey(key, scancode, action, mods);
    Log(Log::Trace, Log::cInput, "Key callback invoked");
}
void InputController::mouseCallback(GLFWwindow* window, int key, int action, int mods)
{
    InputController* controller = static_cast<InputController*>(glfwGetWindowUserPointer(window));
    if (!controller)
    {
        return;
    }
    controller->onMouse(key, action, mods);
    Log(Log::Trace, Log::cInput, "Mouse click callback invoked");
}
void InputController::mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    InputController* controller = static_cast<InputController*>(glfwGetWindowUserPointer(window));
    if (!controller)
    {
        return;
    }
    controller->onScroll(xoffset, yoffset);
    Log(Log::Trace, Log::cInput, "Mouse scroll callback invoked");

}
void InputController::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    InputController* controller = static_cast<InputController*>(glfwGetWindowUserPointer(window));
    if (!controller)
    {
        return;
    }
    controller->onMove(xpos, ypos);
    Log(Log::Trace, Log::cInput, "Cursor position callback invoked");
}


void InputController::onKey(int key, int scancode, int action, int mods)
{
    InputEvent event("key", key, scancode, action, mods);
    Emit_(event);
}
void InputController::onMouse(int key, int action, int mods)
{
    InputEvent event("mouse", key, 0, action, mods);
    Emit_(event);
}
void InputController::onScroll(double xoffset, double yoffset)
{
    MouseScrolledEvent event(xoffset, yoffset);
    Emit_(event);
}
void InputController::onMove(double xpos, double ypos)
{
    MouseMovedEvent event(xpos, ypos);
    Emit_(event);
}


void InputController::createInputEvents(Event& event)
{
    if (event.getEventType() == EventType::MouseScrolled)
    {
        MouseScrolledEvent& mouseEvent = static_cast<MouseScrolledEvent&>(event);
        handleMouseScroll(mouseEvent);
        return;
    }
    if (event.getEventType() == EventType::MouseMoved)
    {
        MouseMovedEvent& mouseEvent = static_cast<MouseMovedEvent&>(event);
        handleMouseMoved(mouseEvent);
        return;
    }

    if (event.getEventType() != EventType::InputEvent)
    {
        Log(Log::Warning, Log::cInput, "Invalid input event {}", event.toString())
        return;
    }
        
    InputEvent& inputEvent = static_cast<InputEvent&>(event);

    if (inputEvent.getType() == "key")
    {
        if (inputEvent.getAction() == GLFW_PRESS)
        {
            KeyPressedEvent keyEvent(inputEvent.getKeycode());
            handleKeyPress (keyEvent);
        }
        if (inputEvent.getAction() == GLFW_RELEASE)
        {
            KeyReleasedEvent keyEvent(inputEvent.getKeycode());
            handleKeyRelease(keyEvent);
        }
        if (inputEvent.getAction() == GLFW_REPEAT)
        {
            KeyRepeatedEvent keyEvent(inputEvent.getKeycode());
            handleKeyRepeat(keyEvent);
        }
        return;
    }

    if (inputEvent.getType() == "mouse")
    {
        if (inputEvent.getAction() == GLFW_PRESS)
        {
            MouseButtonPressedEvent buttonEvent(inputEvent.getKeycode());
            handleMouseClick(buttonEvent);
        }
        if (inputEvent.getAction() == GLFW_RELEASE)
        {
            MouseButtonReleasedEvent buttonEvent(inputEvent.getKeycode());
        }
        return;
    }
}


void InputController::handleKeyPress(KeyPressedEvent& event)
{
    if (event.getKeyCode() == GLFW_KEY_ESCAPE)
    {
        CloseWindow event;
        Emit_(event);
    }
    Log(Log::Trace, Log::cInput, "Key pressed event id: {}", event.getKeyCode());
}


void InputController::handleKeyRelease(KeyReleasedEvent& event)
{
}


void InputController::handleKeyRepeat(KeyRepeatedEvent& event)
{
}


void InputController::handleMouseClick(MouseEvent& event)
{
    Log(Log::Trace, Log::cInput, "Mouse click button event id: {}", event.getButtonCode());
}


void InputController::handleMouseScroll(MouseScrolledEvent& event)
{
    Log(Log::Trace, Log::cInput, "Mouse scroll event offset: y {}", event.getyoffset());
}


void InputController::handleMouseMoved(MouseMovedEvent& event)
{
    Log(Log::Trace, Log::cInput, "Mouse Moved event pos: x {} : y {}", event.getxpos(), event.getypos());
}


