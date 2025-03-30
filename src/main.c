#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "callbacks.h"
#include "renderer.h"
#include "window.h"

#define BUFFER_SIZE 100

const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
    "   gl_PointSize = 1.0f;\n"
    "}\0";

const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
    "}\n\0";


int main()
{ 
  GLFWwindow* window = window_init(WINDOW_WIDTH, WINDOW_HEIGHT);
  if(!window) return -1;

  //callbacks
  glfwSetErrorCallback(error_callback);
  glfwSetKeyCallback(window, key_callback);

  //glad load OpenGL fn pointers
  gladLoadGL(glfwGetProcAddress);

  unsigned int vertexShader = build_vertex_shader(vertexShaderSource); 
  unsigned int fragmentShader = build_fragment_shader(fragmentShaderSource);
  unsigned int shaderProgram = link_shaders(vertexShader, fragmentShader);
  
  //enable pointsize from shader
  //glEnable(GL_PROGRAM_POINT_SIZE);
  
  //set up vertex data, buffers, attributes
  float vertices[BUFFER_SIZE * 2];

  for (int i = 0; i < BUFFER_SIZE; i++)
  {
	float x = (float) i;
	float y = sin((float)i / BUFFER_SIZE * 2.0F * M_PI);
	
	vertices[i * 2] = (2.0F * x / BUFFER_SIZE) - 1.0F;
	vertices[i * 2 + 1] = y;
       	//vertices[i * 3 + 2] = 0.0F; 
  }

  unsigned int VAO, VBO;
  renderer_setup(&VAO, &VBO, sizeof(vertices), vertices);
  
  //render loop
  while(!glfwWindowShouldClose(window))
    {
      render_frame(&shaderProgram, &VAO, (float)BUFFER_SIZE);
      glfwSwapBuffers(window);
      glfwPollEvents();
    }

  //deallocate resources
  renderer_cleanup(&VAO, &VBO, &shaderProgram);
  window_cleanup(window);
  return 0;
}

  
