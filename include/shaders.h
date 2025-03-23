#ifndef SHADERS_H
#define SHADERS_H

unsigned int build_vertex_shader(const char* vertexShaderSource);
unsigned int build_fragment_shader(const char* fragmentShaderSource);
unsigned int link_shaders(unsigned int vertexShader, unsigned int fragmentShader);

#endif


