#include <iostream>
#include <SDL/SDL.h>
#include "Window.h"
#include "Input.h"
#include "Time.h"
#include "Shader.h"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer2D.h"
#include "StaticSprite.h"
#include "GLMOutOverloads.h"
#include "Sprite.h"

int main(int argc, char* args[])
{
	using namespace Silver;

	SDL_Init(SDL_INIT_VIDEO);
	Window w("Silver Engine", 960, 540);	//16:9 aspect ratio
	SDL_GL_SetSwapInterval(0);

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

	Renderer2D renderer;
	std::vector<Renderable2D*> sprites;

	float ttt = 0.09f;
	glm::vec2 ss = glm::vec2(ttt);
	for (float i = -10; i < 10; i += ttt)
		for (float j = -10; j < 10; j += ttt)
			sprites.push_back(new Sprite(glm::vec3(i, j, 0), ss, glm::vec4(glm::abs((i + 10)) / 20.0f, glm::abs((j + 10)) / 20.0f, (glm::abs((i + 10)) / 20.0f + glm::abs((j + 10)) / 20.0f) / 2.0f, 1)));

	float t = 0;
	int f = 0;
	//Game loop
	while (!w.Closed())
	{
		Time::Update();
		t += Time::GetDt();

		if (t >= 1)
		{
			printf("FPS: %i\n", f);
			t = 0;
			f = 0;
		}

		else
		{
			f++;
		}

		Input::Update();
		w.Clear();

		renderer.BeginAdd();
		for (size_t i = 0; i < sprites.size(); i++)
			renderer.Add(sprites[i]);
		renderer.EndAdd();

		renderer.Draw();
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