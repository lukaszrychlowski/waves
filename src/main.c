#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "callbacks.h"
#include "renderer.h"
#include "window.h"

#define BUFFER_SIZE 100

const char* vertexShaderSource = "#version 460 core\n"
    "layout (location = 0) in float y;\n"
    "void main()\n"
    "{\n"
    "   float index = float(gl_VertexID); \n"
    "   gl_Position = vec4(-1.0 + 2.0 * (index / 100.0), y, 0.0, 1.0);\n"
    "   gl_PointSize = 5.0f;\n"
    "}\0";

const char* fragmentShaderSource = "#version 460 core\n"
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
  glEnable(GL_PROGRAM_POINT_SIZE);
  
  //set up vertex data, buffers, attributes
  float vertices[BUFFER_SIZE];
  for (int i = 0; i < BUFFER_SIZE; i++) vertices[i] = sin(((float)i / 100.0F)  * 2.0F * M_PI);

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

  
