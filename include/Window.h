#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <iostream>

class Window {
    public:
        Window(int width, int height, const char* title);
        ~Window();
        GLFWwindow* getGLFWwindow();
        static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

    private:
        GLFWwindow* window;
};
#endif // WINDOW_H