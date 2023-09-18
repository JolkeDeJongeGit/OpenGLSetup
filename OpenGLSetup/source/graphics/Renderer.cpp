#include "Pch.h"
#include "graphics/Renderer.h"
#include "graphics/Camera.h"
#include "graphics/Window.h"
#include "graphics/Mesh.h"
#include "graphics/ShaderManager.h"
#include <gtc/type_ptr.hpp>

namespace Render
{
    GLuint vao;
    Camera debugCamera;
    GLuint shaderProgram;

	Mesh triangle;
	//// Temp Code
	//unsigned int screenWidth = 1920;
	//unsigned int screenHeight = 1080;
	//unsigned int bufferSize;
	//unsigned int* screenBuffer;
}

float Window::MouseXOffset;
float Window::MouseYOffset;

void Render::Init()
{
	//bufferSize = screenWidth * screenHeight;
	//screenBuffer = new unsigned int[bufferSize];

	std::vector<Vertex> Value = {
		Vertex( 0.5f, -0.5f, 0.0f, 0,0,0, 0.0f, 0.0f),
		Vertex( -0.5f, -0.5f, 0.0f, 0,0,0, 1.0f, 0.0f),
		Vertex( 0.0f, 0.5f, 0.0f, 0,0,0, 1.0f, 1.0f),
	};

	std::vector<unsigned int> indices = {  // Note that we start from 0!
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};

	glViewport(0, 0, 1920, 1080);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	Render::debugCamera = Camera();
	ShaderManager::Init();
	shaderProgram = ShaderManager::GetLinkedShader("Basic");
	triangle = Mesh(Value, indices);
}

void Render::Update()
{
    Render::debugCamera.ProcessMouseInput(Window::MouseXOffset, Window::MouseYOffset);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


}

void Render::Render()
{
	ShaderManager::UseShader(shaderProgram);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(Render::debugCamera.GetProjectionMatrix(1920, 1080)));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(Render::debugCamera.GetViewMatrix()));
	triangle.Draw(shaderProgram, glm::identity<glm::mat4>());
	
	//for (unsigned int x = 0; x < screenWidth; x++)
	//{
	//	float xScale = x / float(screenWidth);
	//	for (unsigned int y = 0; y < screenHeight; y++)
	//	{
	//		float yScale = y / float(screenHeight);

	//		screenBuffer[x + y * screenWidth] = (int(yScale * 255.0f) << 8) + (int(xScale * 255.0f));
	//	}
	//}

	//glDrawPixels(screenWidth, screenHeight, GL_RGBA, GL_UNSIGNED_BYTE, screenBuffer);
}

void Render::Shutdown()
{
   
}
