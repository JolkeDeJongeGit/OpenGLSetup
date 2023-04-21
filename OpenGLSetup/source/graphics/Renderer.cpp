#include "Pch.h"
#include "GL/glew.h"
#include "graphics/Renderer.h"
#include "graphics/Camera.h"
#include <graphics/Window.h>

namespace Render::Internal
{
    GLuint vao;
    Camera debugCamera;
    GLuint shader_program;
}

void Render::Init()
{


}

void Render::Update()
{
    Render::Internal::debugCamera.ProcessMouseInput(Window::MouseXOffset, Window::MouseYOffset);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

}

void Render::Render()
{
}

void Render::Shutdown()
{
   
}
