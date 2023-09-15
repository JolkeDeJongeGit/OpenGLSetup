#pragma once

class Window;
namespace Engine
{
    void Init();
    void Update(const float dt);
    void Shutdown();
    bool ShouldQuit();

    Window* GetWindow();
}