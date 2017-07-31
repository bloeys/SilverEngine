#include <iostream>
#include <SDL/SDL.h>
#include "Window.h"
#include "Input.h"

int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_VIDEO);
	Silver::Window w("Silver Engine", 960, 540);	//16:9 aspect ratio

	SDL_Keycode keys[] = { SDLK_SPACE };
	Silver::Input::RegisterButton("Jump", keys, 1);
	SDL_Keycode keys2[] = { SDLK_a};
	Silver::Input::UpdateButton("Jump", keys2, 1);

	//Game loop
	while (!w.Closed())
	{
		Silver::Input::Update();
		w.Update();

		if (Silver::Input::IsButtonPressed("Jump"))
			std::cout << "Jumping!" << std::endl;
	}
	SDL_Quit();

	return 0;
}