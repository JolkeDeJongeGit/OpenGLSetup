#pragma once
namespace Debug
{
	void Init();
	void Update(const float dt);
	void Render();
	bool Paused();
	void Shutdown();
}