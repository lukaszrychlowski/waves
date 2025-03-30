#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

GLFWwindow* window_init(int width, int height);
void window_cleanup(GLFWwindow* window);

#endif

