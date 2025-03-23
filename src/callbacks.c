#include "callbacks.h"

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		printf("ESC pressed\n");
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

