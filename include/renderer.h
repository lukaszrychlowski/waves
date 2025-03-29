#ifndef RENDERER_H
#define RENDERER_H

unsigned int build_vertex_shader(const char* vertexShaderSource);
unsigned int build_fragment_shader(const char* fragmentShaderSource);
unsigned int link_shaders(unsigned int vertexShader, unsigned int fragmentShader);
unsigned int renderer_setup(unsigned int* VAO, unsigned int* VBO, size_t size_vertices, float* vertices);
void render_frame(unsigned int shader_program, unsigned int* VAO, float no_of_vertices);
void renderer_cleanup(unsigned int VAO, unsigned int VBO, unsigned int shaderProgram);

#endif

