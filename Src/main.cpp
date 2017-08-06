#include <iostream>
#include <SDL/SDL.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Time.h"
#include "Input.h"
#include "Window.h"
#include "GLMOutOverloads.h"

#include "Graphics/Shader.h"
#include "Graphics/Sprite.h"
#include "Graphics/Renderer2D.h"
#include "Graphics/MainLayer2D.h"

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

	Shader* s = new Shader(R"(Shaders\Test.vert)", R"(Shaders\Test.frag)");
	s->Enable();
	s->AddUniform("projectionMat");
	MainLayer2D layer((Renderer2DBase*)new Renderer2D(), s, glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, -1.0f));

	Shader* s2 = new Shader(R"(Shaders\Test.vert)", R"(Shaders\Test.frag)");
	s2->Enable();
	s2->AddUniform("projectionMat");
	MainLayer2D layer2((Renderer2DBase*)new Renderer2D(), s2, glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, -1.0f));

	float ttt = 0.09f;
	glm::vec2 ss = glm::vec2(ttt);
	for (float i = -10; i < 0; i += ttt)
		for (float j = -10; j < 10; j += ttt)
			layer.Add(new Sprite(glm::vec3(i, j, 0), ss, glm::vec4(glm::abs((i + 10)) / 20.0f, glm::abs((j + 10)) / 20.0f, (glm::abs((i + 10)) / 20.0f + glm::abs((j + 10)) / 20.0f) / 2.0f, 1)));

	for (float i = 0; i < 10; i += ttt)
		for (float j = -10; j < 10; j += ttt)
			layer2.Add(new Sprite(glm::vec3(i, j, 0), ss, glm::vec4(glm::abs((i + 10)) / 20.0f, glm::abs((j + 10)) / 20.0f, (glm::abs((i + 10)) / 20.0f + glm::abs((j + 10)) / 20.0f) / 2.0f, 1)));

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

		layer.Draw();
		layer2.Draw();
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