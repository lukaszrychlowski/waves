#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define BUFFER_SIZE 10

void error_callback(int error, const char* description);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
GLFWwindow* create_window(unsigned int width, unsigned int height);
unsigned int build_vertex_shader(const char* vertexShaderSource);
unsigned int build_fragment_shader(const char* fragmentShaderSource);
unsigned int link_shaders(unsigned int vertexShader, unsigned int fragmentShader);

const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "   gl_PointSize = 1.0f;\n"
    "}\0";

const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.6f, 0.2f, 1.0f);\n"
    "}\n\0";

int main()
{
  //generate seed
  srand(time(NULL));
  int x = rand();
  int y = rand();
  //init
  glfwInit();
  if (!glfwInit())
  {
    fprintf(stderr, "failed to init glfw\n");
  }
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
  glEnable(GL_PROGRAM_POINT_SIZE);
  
  //set up vertex data, buffers, attributes
  float vertices[BUFFER_SIZE * 3] = {};

  for (int i = 0; i < BUFFER_SIZE; i++)
  {
	float x = (float) i;
	float y = sin((float)i / BUFFER_SIZE * 2.0F * M_PI);
	
	vertices[i * 3] = (2.0F * x / BUFFER_SIZE) - 1.0F;
	vertices[i * 3 + 1] = y;
       	vertices[i * 3 + 2] = 0.0F; 
  }

  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  //render loop
  while(!glfwWindowShouldClose(window))
    {
      //bg color      
      glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      glUseProgram(shaderProgram);
      glBindVertexArray(VAO);
      const float no_of_vertices = sizeof(vertices) / (3 * sizeof(float)); 
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

void error_callback(int error, const char* description)
{
  fprintf(stderr, "Err: %s\n", description);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
      glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
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
  //delete shaders after linking
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  return shaderProgram;
}
  
