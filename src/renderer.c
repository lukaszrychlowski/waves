#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "renderer.h"

unsigned int build_vertex_shader(const char* vertexShaderSource)
{
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
    {
      glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
      printf("failed to compile vertex shader\n");
      printf(infoLog);
    }
  return vertexShader;
}

unsigned int build_fragment_shader(const char* fragmentShaderSource)
{
  int success;
  char infoLog[512];
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success)
    {
      glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
      printf("failed to compile fragment shader\n");
      printf(infoLog);
    }
  return fragmentShader;
}

unsigned int link_shaders(unsigned int vertexShader, unsigned int fragmentShader)
{
  int success;
  char infoLog[512];
  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success)
    {
      glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
      printf( "failed to compile shader program\n");
      printf(infoLog);
    }
  return shaderProgram;
}

void renderer_setup(unsigned int* VAO, unsigned int* VBO, size_t size_vertices, float* vertices)
{ 
    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);
    glBindVertexArray(*VAO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, size_vertices, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void render_frame(unsigned int* shader_program, unsigned int* VAO, float no_of_vertices)
{
    glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(*shader_program);
    glBindVertexArray(*VAO);
    glDrawArrays(GL_POINTS, 0, no_of_vertices); 
}

void renderer_cleanup(unsigned int* VAO, unsigned int* VBO, unsigned int* shaderProgram)
{
    glDeleteVertexArrays(1, VAO);
    glDeleteBuffers(1, VBO);
    glDeleteProgram(shaderProgram);
}
