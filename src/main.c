#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#include "callbacks.h"
#include "renderer.h"
#include "window.h"
#include "sound.h"

#define BUFFER_SIZE 10

static float map(float val, float in_min, float in_max, float out_min, float out_max);

const char* vertexShaderSource = "#version 460 core\n"
    "layout (location = 0) in float y;\n"
    "float map(float val, float in_min, float in_max, float out_min, float out_max)\n"
    "{\n"
    "   return out_min + (out_max - out_min) * (val - in_min) / (in_max - in_min); \n"
    "}\n"
    "void main()\n"
    "{\n"
    "   float x = map((float(gl_VertexID)), 0.0, 9.0, -1.0, 1.0); \n"
    "   float val = map(y, -1.0, 1.0, -1.0, 1.0);\n"
    "   gl_Position = vec4(x, y, 0.0, 1.0);\n"
    "   gl_PointSize = 1.0f;\n"
    "}\0";

const char* fragmentShaderSource = "#version 460 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
    "}\0";


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
  for (int i = 0; i < BUFFER_SIZE; i++)
  {   
      float j = map((float)i, 0.0F, BUFFER_SIZE-1.0F, -1.0, 1.0);
      vertices[i] = sin(j * 2.0F * M_PI);
  }
  unsigned int VAO, VBO;
  renderer_setup(&VAO, &VBO, sizeof(vertices), vertices);
  //threads
  pthread_t thread;
  int rc = pthread_create(&thread, NULL, capture_audio, NULL);  
  if(rc)
  {
    printf("pthread_create failed\n");
    return -1;
  }
  //capture_audio();
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

static float map(float val, float in_min, float in_max, float out_min, float out_max)
{   
    return out_min + (out_max - out_min) * (val - in_min) / (in_max - in_min);
}
