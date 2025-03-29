#include "window.h"
#include <stdio.h>

GLFWwindow* window_init(int width, int height)
{
    if(!glfwInit())
    {
        fprintf(stderr, "failed to init glfw\n");
        return NULL;
    }
    GLFWwindow* window = glfwCreateWindow(width, height, "", NULL, NULL);
    glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_FALSE);
    if(!window)
    {
        glfwTerminate();
        fprintf(stderr, "failed to create a window\n");
        return NULL;
    }
    glfwMakeContextCurrent(window);
    return window;
}

void window_cleanup(GLFWwindow* window)
{
    glfwDestroyWindow(window);
    glfwTerminate();
}
