#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"

class Window 
{
public:
    Window() = default;
    Window(int width, int height, const char* title) 
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);
        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK) {
            std::cerr << "Failed to initialize GLEW" << std::endl;
            glfwTerminate();
        }
    }

    ~Window() 
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    inline bool ShouldClose() const 
    {
        return glfwWindowShouldClose(window);
    }

    inline void Update() 
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    inline GLFWwindow* GetWindow() { return window; };

    inline void SetIcon(int count, const GLFWimage* images) 
    {
        glfwSetWindowIcon(window, count, images);
    }

private:
    GLFWwindow* window;
};