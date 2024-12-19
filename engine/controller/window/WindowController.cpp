#include "WindowController.h"

WindowController::WindowController()
{
    Log_(Log::System, Log::cWindow, "Initializing..")
    createListeners();
};
WindowController::~WindowController()
{
};

void WindowController::createListeners()
{
    using namespace std::placeholders;
    Listener_(EventType::CloseWindow, std::bind(&WindowController::closeWindow, this, _1))
}

void WindowController::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void WindowController::window_size_callback(GLFWwindow* window, int width, int height)
{
    WindowController* controller = static_cast<WindowController*>(glfwGetWindowUserPointer(window));
    if (controller)
    {
        controller->width                       = width;
        controller->height                      = height;
    }
}


void WindowController::window_refresh_callback(GLFWwindow* window)
{
    glfwSwapBuffers(window);
}


void WindowController::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    WindowController* controller = static_cast<WindowController*>(glfwGetWindowUserPointer(window));
    if (controller)
    {
        controller->onKey(key, scancode, action, mods);
    }
}

void WindowController::mouseCallback(GLFWwindow* window, int key, int action, int mods)
{
    WindowController* controller = static_cast<WindowController*>(glfwGetWindowUserPointer(window));
    if (controller)
    {
        controller->onMouse(key, action, mods);
    }
}

void WindowController::mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    WindowController* controller = static_cast<WindowController*>(glfwGetWindowUserPointer(window));
    if (controller)
    {
        controller->onScroll(xoffset, yoffset);
    }
}

void WindowController::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    WindowController* controller = static_cast<WindowController*>(glfwGetWindowUserPointer(window));
    if (controller)
    {
        controller->onMove(xpos, ypos);
    }
}


void WindowController::onKey(int key, int scancode, int action, int mods)
{
    InputEvent event("key", key, scancode, action, mods);
    Emit_(event);
}

void WindowController::onMouse(int key, int action, int mods)
{
    InputEvent event("mouse", key, 0, action, mods);
    Emit_(event);
}

void WindowController::onScroll(double xoffset, double yoffset)
{
    MouseScrolledEvent event(xoffset, yoffset);
    Emit_(event);
}

void WindowController::onMove(double xpos, double ypos)
{
    MouseMovedEvent event(xpos, ypos);
    Emit_(event);
}


bool WindowController::initialize()
{
    if(!glfwInit())
    {
        Log_(Log::Fatal, Log::cWindow, "Failed to initialize GLFW");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_AUTO_ICONIFY, GL_FALSE);


    window = glfwCreateWindow(width, height, title, NULL, NULL );

    if (!window)
    {
        Log_(Log::Fatal, Log::cWindow, "Failed to initialize window");
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetWindowUserPointer(window, this);

    glfwSetWindowRefreshCallback(window, window_refresh_callback);

    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseCallback);
    glfwSetScrollCallback(window, mouseScrollCallback);
    // glfwSetCursorPosCallback(window, cursorPositionCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Log_(Log::Fatal, Log::Engine, "Failed to initialize GLAD");
        return false;
    }

    glViewport(0, 0, width, height);

    Log_(Log::System, Log::cWindow, "Initialized successfully!")
    return true;
}


bool WindowController::active()
{
    return glfwWindowShouldClose(window) == GLFW_FALSE;
}


void WindowController::pollEvents()
{
    glfwPollEvents();
}


void WindowController::windowRefresh()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
}


void WindowController::clear()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
}


void WindowController::swapBuffers()
{
    glfwSwapBuffers(window);
}

void WindowController::closeWindow(Event& event)
{
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void WindowController::terminate()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}