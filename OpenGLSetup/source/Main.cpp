#include "Pch.h"
#include "Engine.h"

int main()
{
    Engine::Init();
    std::chrono::steady_clock::time_point previous_time = std::chrono::high_resolution_clock::now();
    while (!Engine::ShouldQuit())
    {
        std::chrono::steady_clock::time_point current_time = std::chrono::high_resolution_clock::now();
        float delta_time = static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(current_time - previous_time).count()) * 0.001f;
        previous_time = current_time;
        Engine::Update(delta_time);
    }

    return 0;
}