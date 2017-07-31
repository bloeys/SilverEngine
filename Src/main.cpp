#include <iostream>
#include <SDL/SDL.h>
#include "Window.h"
#include "Input.h"
#include "Time.h"

int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_VIDEO);
	Silver::Window w("Silver Engine", 960, 540);	//16:9 aspect ratio

	SDL_Keycode keys[] = { SDLK_SPACE };
	SDL_Keycode mods[] = { SDLK_LCTRL };
	Silver::Input::RegisterButton("Jump", keys, mods, 1, 1);

	float dt = 16.0f / 1000.0f;

	//Game loop
	while (!w.Closed())
	{
		Silver::Time::Update();
		Silver::Input::Update();
		w.Update();

		if (Silver::Input::IsButtonPressed("Jump"))
			std::cout << "Jumping!" << std::endl;
		if (Silver::Input::IsMousePressed(1))
			std::cout << "Mouse Left!" << std::endl;
		if (Silver::Input::IsMouseHeld(2))
			std::cout << "Mouse Middle!" << std::endl;
		if (Silver::Input::IsMouseReleased(3))
			std::cout << "Mouse Right!" << std::endl;
	}
	SDL_Quit();

	return 0;
}