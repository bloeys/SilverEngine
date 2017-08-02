#include <iostream>
#include <SDL/SDL.h>
#include "Window.h"
#include "Input.h"
#include "Time.h"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer2D.h"
#include "GLMOutOverloads.h"
int main(int argc, char* args[])
{
	using namespace Silver;

	SDL_Init(SDL_INIT_VIDEO);
	Window w("Silver Engine", 960, 540);	//16:9 aspect ratio

	SDL_Keycode keys[] = { SDLK_SPACE };
	SDL_Keycode mods[] = { SDLK_LCTRL };
	Input::RegisterButton("Jump", keys, mods, 1, 1);

	float dt = 16.0f / 1000.0f;

	Shader s(R"(c:\Users\omarm\Documents\Visual Studio 2017\Projects\C++\SilverEngine\SilverEngine\Shaders\Test.vert)",
		R"(c:\Users\omarm\Documents\Visual Studio 2017\Projects\C++\SilverEngine\SilverEngine\Shaders\Test.frag)");
	s.Enable();
	s.AddUniform("projectionMat");
	s.AddUniform("modelMat");
	s.SetUniform("projectionMat", glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, -1.0f));

	Renderable2D sprite1(glm::vec3(0, 8, 0), glm::vec2(2, 2), s), sprite2(glm::vec3(5, 5, 0), glm::vec2(2, 2), glm::vec4(1,0,0,1), s);
	Renderer2D renderer;

	//Game loop
	while (!w.Closed())
	{
		Time::Update();
		Input::Update();
		
		w.Clear();
		renderer.Draw(&sprite1);
		renderer.Draw(&sprite2);
		renderer.Flush();
		w.Update();

		if (Input::IsButtonPressed("Jump"))
			std::cout << "Jumping!" << std::endl;
		if (Input::IsMousePressed(1))
			std::cout << "Mouse Left!" << std::endl;
		if (Input::IsMouseHeld(2))
			std::cout << "Mouse Middle!" << std::endl;
		if (Input::IsMouseReleased(3))
			std::cout << "Mouse Right!" << std::endl;
	}
	SDL_Quit();

	return 0;
}