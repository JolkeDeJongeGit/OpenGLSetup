#include "Pch.h"
#include "graphics/Window.h"
#pragma warning( push )
#pragma warning(push, 0)
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#pragma warning( pop ) 

void Window::SetIcon(int count, const char* name)
{
    if (windowIconImage)
    {
        delete windowIconImage;
        windowIconImage = nullptr;
    }

    windowIconImage = new GLFWimage();
    int width, height, channels;
    unsigned char* image_data = stbi_load(name, &width, &height, &channels, 0);

    // Create a GLFW image structure
    windowIconImage->width = width;
    windowIconImage->height = height;
    windowIconImage->pixels = image_data;
    glfwSetWindowIcon(window, count, windowIconImage);
    stbi_image_free(windowIconImage->pixels);
}
