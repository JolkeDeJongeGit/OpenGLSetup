#include "Pch.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "subsystem/DebugManager.h"
#include "Engine.h"

void Debug::Init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplGlfw_InitForOpenGL(Engine::GetWindow()->GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void Debug::Update()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Debug::Render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Debug::Shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
