#include <iostream>
#include <SDL\SDL.h>
#include "Window.h"

int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_VIDEO	);
	Window w("Silver Engine", 960, 540);	//16:9 aspect ratio

	//Game loop
	while (!w.Closed())
	{
		w.Update();
	}
	SDL_Quit();

	return 0;
}