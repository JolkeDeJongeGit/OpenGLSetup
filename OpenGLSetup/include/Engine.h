#pragma once
#include "graphics/Window.h"
namespace Engine
{
    void Init();
    void Update(const float dt);
    void Shutdown();
    bool ShouldQuit();

    Window* GetWindow();
}