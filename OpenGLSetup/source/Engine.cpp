#include "Pch.h"
#include "Engine.h"
#pragma warning( push )
#pragma warning(push, 0)
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#pragma warning( pop ) 

#include "graphics/Renderer.h"

namespace Engine::Internal
{
	Window* window; 
	bool is_running = true;
}

void Engine::Init()
{
	GLFWimage images[1];
	int width, height, channels;
	unsigned char* image_data = stbi_load("assets/icon.png", &width, &height, &channels, 0);

	// Create a GLFW image structure
	images[0].width = width;
	images[0].height = height;
	images[0].pixels = image_data;
	Engine::Internal::window = new Window(1920, 1080, "Template Window");
	Engine::Internal::window->SetIcon(1, images);
	stbi_image_free(images[0].pixels);

	Render::Init();
}

void Engine::Update(const float dt)
{
	{
		Render::Update();
		Render::Render();
	}

	Engine::Internal::window->Update();
	printf("%f \n", dt);
}

void Engine::Shutdown()
{
    Render::Shutdown();
}

bool Engine::ShouldQuit()
{
	return Engine::Internal::window->ShouldClose();
}

Window* Engine::GetWindow()
{
    return Engine::Internal::window;
}
