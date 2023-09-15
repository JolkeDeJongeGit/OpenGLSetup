#include "Pch.h"
#include "Engine.h"
#include "subsystem/DebugManager.h"
#include "graphics/Renderer.h"
#include "graphics/Window.h"

namespace Engine
{
	Window* window; 
	bool is_running = true;
}

void Engine::Init()
{
	window = new Window(1920, 1080, "Template Window");
	window->SetIcon(1, "assets/icon.png");

	Render::Init();
	Debug::Init();
}

void Engine::Update(const float dt)
{
	Debug::Update(dt);
	if(!Debug::Paused())
	{
		Render::Update();
		Render::Render();
	}
	Debug::Render();
	window->Update();
}

void Engine::Shutdown()
{
	Debug::Shutdown();
    Render::Shutdown();
}

bool Engine::ShouldQuit()
{
	return window->ShouldClose();
}

Window* Engine::GetWindow()
{
    return Engine::window;
}
