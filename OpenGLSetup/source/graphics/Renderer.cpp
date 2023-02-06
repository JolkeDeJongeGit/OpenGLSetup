#include "Pch.h"
#include "GL/glew.h"
#include "graphics/Renderer.h"

namespace Render::Internal
{
    GLuint vao;
    GLuint shader_program;
}

void Render::Init()
{
    glGenVertexArrays(1, &Internal::vao);
    glBindVertexArray(Internal::vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexShaderSource = "#version 400 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderSource = "#version 400 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    Internal::shader_program = glCreateProgram();
    glAttachShader(Internal::shader_program, vertexShader);
    glAttachShader(Internal::shader_program, fragmentShader);
    glLinkProgram(Internal::shader_program);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

}

void Render::Update()
{

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(Internal::shader_program);
    glBindVertexArray(Internal::vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Render::Render()
{
}

void Render::Shutdown()
{
}
