#include "WindowController.h"

#include "CoreEvent.h"
#include "RenderGladGLFW.h"


WindowController::WindowController()
{
    LogStartup(Log::cWindow);
    try
    {
        registerListeners();
        initialize();
    }
    catch(Exceptions)
    {
        LogFailure(Log::cWindow, error);
    }
    LogSuccess(Log::cWindow);
};

WindowController::~WindowController()
{

};


void WindowController::registerListeners()
{
    Listener_(EventType::CloseWindow, std::bind(&WindowController::closeWindow, this, std::placeholders::_1));
}


void GLAPIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    Throw(Error::runtime, "::[{}] OpenGL debug message: {}", severity, message);
}


void setupDebugCallback()
{
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    glDebugMessageControl (GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);

    glDebugMessageControl (GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_HIGH,   0, nullptr, GL_TRUE);
    glDebugMessageControl (GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_MEDIUM, 0, nullptr, GL_TRUE);
    glDebugMessageControl (GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_LOW,    0, nullptr, GL_TRUE);
    glDebugMessageCallback(debugCallback, nullptr);
}


void WindowController::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    WindowController* controller = static_cast<WindowController*>(glfwGetWindowUserPointer(window));
    
    if (!controller) return;

    glViewport(0, 0, width, height);
}


void WindowController::window_size_callback(GLFWwindow* window, int width, int height)
{
    WindowController* controller = static_cast<WindowController*>(glfwGetWindowUserPointer(window));
    
    if (!controller) return;
    
    controller->width                       = width;
    controller->height                      = height;
}


void WindowController::window_refresh_callback(GLFWwindow* window)
{
    glfwSwapBuffers(window);
}


void WindowController::initialize()
{
    if(!glfwInit())
    {
        Throw(Error::runtime, "Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_AUTO_ICONIFY, GL_FALSE);

    window = glfwCreateWindow(width, height, title, NULL, NULL );

    if (!window)
    {
        Throw(Error::runtime, "Failed to initialize window")
    }

    glfwMakeContextCurrent(window);

    glfwSwapInterval(0);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetWindowUserPointer(window, this);

    glfwSetWindowRefreshCallback(window, window_refresh_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Throw(Error::runtime, "Failed to initialize GLAD")
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


void WindowController::shutdown()
{
    glfwDestroyWindow(window);
    glfwTerminate();
    LogPowerDown(Log::cWindow);
}

