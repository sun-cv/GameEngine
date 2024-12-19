#include "InputController.h"


InputController::InputController()
{
    Log_(Log::System, Log::cInput, "Initializing..")
    createListeners();
    Log_(Log::System, Log::cInput, "Initialized successfully!")
}


InputController::~InputController()
{
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
        Log_(Log::Warning, Log::cInput, "Invalid input event {}", event.toString())
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
    Log_(Log::Debug, Log::cInput, "Key pressed event id: {}", event.getKeyCode());
}


void InputController::handleKeyRelease(KeyReleasedEvent& event)
{

}


void InputController::handleKeyRepeat(KeyRepeatedEvent& event)
{

}



void InputController::handleMouseClick(MouseEvent& event)
{
    Log_(Log::Debug, Log::cInput, "Mouse click button event id: {}", event.getButtonCode());
}


void InputController::handleMouseScroll(MouseScrolledEvent& event)
{
    Log_(Log::Debug, Log::cInput, "Mouse scroll event offset: y {}", event.getyoffset());
}


void InputController::handleMouseMoved(MouseMovedEvent& event)
{
    Log_(Log::Debug, Log::cInput, "Mouse Moved event pos: x {} : y {}", event.getxpos(), event.getypos());
}


void InputController::createListeners()
{
    using namespace std::placeholders;

    Listener_(EventType::InputEvent, std::bind(&InputController::createInputEvents, this, _1));
    Listener_(EventType::MouseScrolled, std::bind(&InputController::createInputEvents, this, _1));
    Listener_(EventType::MouseMoved, std::bind(&InputController::createInputEvents, this, _1));
}