#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

GLFWwindow* window_init(int width, int height);
void window_cleanup(GLFWwindow* window);

#endif

