#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "callbacks.h"
#include "shaders.h"

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

GLFWwindow* create_window(unsigned int width, unsigned int height);

int main()
{
  //generate seed
  srand(time(NULL));
  int x = rand();
  int y = rand();
  
  //init
  if(!glfwInit())
  {
	fprintf(stderr, "failed to init glfw\n");
  	return 1;
  }
  
  //create window
  GLFWwindow* window = create_window(640, 480);
  
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
  float vertices[BUFFER_SIZE * 2] = {};

  for (int i = 0; i < BUFFER_SIZE; i++)
  {
	float x = (float) i;
	float y = sin((float)i / BUFFER_SIZE * 2.0F * M_PI);
	
	vertices[i * 2] = (2.0F * x / BUFFER_SIZE) - 1.0F;
	vertices[i * 2 + 1] = y;
       	//vertices[i * 3 + 2] = 0.0F; 
  }

  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  //render loop
  while(!glfwWindowShouldClose(window))
    {
      //bg color      
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      glUseProgram(shaderProgram);
      glBindVertexArray(VAO);
      const float no_of_vertices = (float)BUFFER_SIZE;
      glDrawArrays(GL_LINE_STRIP, 0, no_of_vertices);
      glfwSwapBuffers(window);
      glfwPollEvents();
    }

  //deallocate resources
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);

  //terminate glfw
  glfwTerminate();
  return 0;
}

GLFWwindow* create_window(unsigned int width, unsigned int height)
{
  GLFWwindow* window = glfwCreateWindow(width, height, "", NULL, NULL);
  glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_FALSE);
  if (!window)
  {
     glfwTerminate();
     fprintf(stderr, "failed to create a window\n");
  }
  glfwMakeContextCurrent(window);
  return window;
}

  
