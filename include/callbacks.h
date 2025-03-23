#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <stdio.h>
#include <GLFW/glfw3.h>

void error_callback(int error, const char* description);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
//void framebuffer_size_callback(GLFWwindow* window, int width, int height); not used currently

#endif

