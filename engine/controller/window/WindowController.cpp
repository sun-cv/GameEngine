#include "WindowController.h"

WindowController::WindowController()
{
    Log_(Log::System, Log::cWindow, "Initializing..")
    registerListeners();
    initialize();
    Log_(Log::System, Log::cWindow, "Initialized successfully!")

};
WindowController::~WindowController()
{
};

void WindowController::registerListeners()
{
    using namespace std::placeholders;
    Listener_(EventType::CloseWindow, std::bind(&WindowController::closeWindow, this, _1))
}

void GLAPIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    Log_(Log::Error, Log::OpenGL, "::[{}] Debug message: {}", severity, message);
}

void setupDebugCallback()
{
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);

    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_HIGH, 0, nullptr, GL_TRUE);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_MEDIUM, 0, nullptr, GL_TRUE);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_LOW, 0, nullptr, GL_TRUE);
    glDebugMessageCallback(debugCallback, nullptr);
}

void WindowController::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{

    WindowController* controller = static_cast<WindowController*>(glfwGetWindowUserPointer(window));
    if (controller)
    {
        glViewport(0, 0, width, height);
    }
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



void WindowController::initialize()
{
    if(!glfwInit())
    {
        Log_(Log::Fatal, Log::cWindow, "Failed to initialize GLFW");
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_AUTO_ICONIFY, GL_FALSE);

    window = glfwCreateWindow(width, height, title, NULL, NULL );

    if (!window)
    {
        Log_(Log::Fatal, Log::cWindow, "Failed to initialize window");
        return;
    }

    glfwMakeContextCurrent(window);

    glfwSwapInterval(0);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetWindowUserPointer(window, this);

    glfwSetWindowRefreshCallback(window, window_refresh_callback);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Log_(Log::Fatal, Log::Engine, "Failed to initialize GLAD");
        return;
    }

    glViewport(0, 0, width, height);

    setupDebugCallback();
}




bool WindowController::active()
{
    return glfwWindowShouldClose(window) == GLFW_FALSE;
}


void WindowController::pollEvents()
{
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwPollEvents();

}


void WindowController::windowRefresh()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
}


void WindowController::clear()
{
    glClearColor(0, 0, 0, 1);
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

