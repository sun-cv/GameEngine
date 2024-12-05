#include "WindowManager.h"

WindowManager::WindowManager() {}

WindowManager::~WindowManager() {}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); };
bool WindowManager::initialize() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WindowManager::width, WindowManager::height, WindowManager::title, nullptr, nullptr);

    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetWindowUserPointer(window, this);
    glfwSetWindowRefreshCallback(window, [](GLFWwindow* win) {
        WindowManager* manager = static_cast<WindowManager*>(glfwGetWindowUserPointer(win));
        if (manager) {
            manager->windowRefresh();
        }
    });

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glViewport(0, 0, WindowManager::width, WindowManager::height);

    return true;
}

void WindowManager::windowRefresh() {
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
}

void WindowManager::pollEvents() { glfwPollEvents(); }

void WindowManager::clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
    ;
}

void WindowManager::swapBuffers() { glfwSwapBuffers(window); };

void WindowManager::terminate() {
    glfwDestroyWindow(window);
    glfwTerminate();
};

bool WindowManager::active() const { return glfwWindowShouldClose(window) == GLFW_FALSE; };