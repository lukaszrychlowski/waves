#ifndef SHADERS_H
#define SHADERS_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "shaders.h"

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

#endif

