#include <SDL/SDL_timer.h>
#include "Time.h"

namespace Silver {
	float Time::dt = 0;
	size_t Time::lastTickTime = 0;

	void Time::Update()
	{
		size_t ticks = SDL_GetTicks();
		dt = (ticks - lastTickTime) / 1000.0f;
		lastTickTime = ticks;
	}
}