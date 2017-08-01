#include <SDL/SDL.h>
#include "Input.h"
#include "Time.h"

namespace Silver {

	size_t Input::keysPressed = 0;
	Input::MouseInfo Input::mouseInfo;
	std::vector<SDL_WindowEventID> Input::windowEvents = {};
	std::unordered_map <SDL_Keycode, Input::KeyInfo> Input::keys = {};
	std::unordered_map <std::string, Input::Button> Input::buttons = {};
	std::unordered_map <SDL_Keycode, Input::KeyInfo>::iterator Input::it = Input::keys.begin();

	void Input::Update()
	{
		for (it = keys.begin(); it != keys.end(); it++)
		{
			if (it->second.secondsSinceRelease <= 0.5f)
				it->second.secondsSinceRelease += Time::GetDt();

			it->second.pressedThisFrame = false;
		}

		for (size_t i = 0; i < 5; i++)
		{
			mouseInfo.mouseBtns[i].clicks = 0;
			mouseInfo.mouseBtns[i].pressedThisFrame = mouseInfo.mouseBtns[i].releasedThisFrame = false;
		}
		windowEvents.clear();

		SDL_Event ev;
		while (SDL_PollEvent(&ev))
		{
			switch (ev.type)
			{
				//Keyboard
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

			//Mouse
			case SDL_KEYUP:
				keys[ev.key.keysym.sym].secondsSinceRelease = 0;
				keys[ev.key.keysym.sym].isPressed = false;
				keysPressed--;
				break;
			case SDL_MOUSEMOTION:
				mouseInfo.prevX = mouseInfo.x;
				mouseInfo.prevY = mouseInfo.y;
				mouseInfo.x = ev.button.x;
				mouseInfo.y = ev.button.y;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (!mouseInfo.mouseBtns[ev.button.button].isPressed)
					mouseInfo.mouseBtns[ev.button.button].pressedThisFrame = true;

				mouseInfo.mouseBtns[ev.button.button].clicks = ev.button.clicks;
				mouseInfo.mouseBtns[ev.button.button].isPressed = true;
				break;
			case SDL_MOUSEBUTTONUP:
				mouseInfo.mouseBtns[ev.button.button].releasedThisFrame = true;
				mouseInfo.mouseBtns[ev.button.button].isPressed = false;
				break;

				//Window
			case SDL_WINDOWEVENT:
				windowEvents.emplace_back((SDL_WindowEventID)ev.window.event);
				break;
			}
		}
	}

	bool Input::RegisterButton(const std::string &btnName, const SDL_Keycode* requiredKeys, const SDL_Keycode* requiredMods, const size_t keyCount, const size_t modCount)
	{
		if (keyCount == 0 || buttons.find(btnName) != buttons.end())
			return false;

		Button *b = new Button(btnName, requiredKeys, requiredMods, keyCount, modCount);
		buttons[btnName] = *b;
		return true;
	}

	void Input::UpdateButton(const std::string &btnName, const SDL_Keycode* requiredKeys, const SDL_Keycode* requiredMods, const size_t keyCount, const size_t modCount)
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