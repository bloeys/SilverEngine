#include <SDL/SDL.h>
#include "Input.h"
#include "Time.h"

namespace Silver {

	size_t Input::keysPressed = 0;
	std::vector<SDL_WindowEventID> Input::windowEvents = {};
	std::unordered_map <SDL_Keycode, Input::KeyInfo> Input::keys = {};
	std::unordered_map <std::string, Input::Button> Input::buttons = {};
	std::unordered_map <SDL_Keycode, Input::KeyInfo>::iterator Input::it = Input::keys.begin();

	void Input::Update()
	{
		for (it = keys.begin(); it != keys.end(); it++)
		{
			if (it->second.secondsSinceRelease <= 0.5)
				it->second.secondsSinceRelease += Time::GetDt();
			it->second.pressedThisFrame = false;
		}

		windowEvents.clear();

		SDL_Event ev;
		while (SDL_PollEvent(&ev))
		{
			switch (ev.type)
			{
			case SDL_KEYDOWN:
			{
				SDL_Keycode code = ev.key.keysym.sym;

				if (keys.find(code) == keys.end())
					keys[code] = KeyInfo();

				if (!keys[code].isPressed)
					keys[code].pressedThisFrame = true;

				keys[code].isPressed = true;
				keysPressed++;
			}
			break;
			case SDL_KEYUP:
				if (keys[ev.key.keysym.sym].isPressed)
					keys[ev.key.keysym.sym].secondsSinceRelease = 0;

				keys[ev.key.keysym.sym].isPressed = false;
				keysPressed--;
				break;
			case SDL_WINDOWEVENT:
				windowEvents.emplace_back((SDL_WindowEventID)ev.window.event);
				break;
			}
		}
	}

	bool Input::RegisterButton(const std::string &btnName, SDL_Keycode* requiredKeys, SDL_Keycode* requiredMods, size_t keyCount, size_t modCount)
	{
		if (keyCount == 0 || buttons.find(btnName) != buttons.end())
			return false;

		Button *b = new Button(btnName, requiredKeys, requiredMods, keyCount, modCount);
		buttons[btnName] = *b;
		return true;
	}

	void Input::UpdateButton(const std::string &btnName, SDL_Keycode* requiredKeys, SDL_Keycode* requiredMods, size_t keyCount, size_t modCount)
	{
		if (buttons.find(btnName) == buttons.end())
			return;

		buttons[btnName].UpdateKeys(requiredKeys, requiredMods, keyCount, modCount);
	}

	void Input::DeleteButton(const std::string &btnName)
	{
		if (buttons.find(btnName) != buttons.end())
			buttons.erase(btnName);
	}
}