#define GL_SILENCE_DEPRECATION  // Recieve warnings since OpenGl has been replaced with Metal for MacOS
#include <Window.h>

Window::Window(int width, int height, const char* title) {
    if(!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(-1); // Terminate program
    }

    //Use OpenGL Version 4.1 (Highest version usable on MacOS)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if(!window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow * Window::getGLFWwindow() {
    return window;
}



void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}