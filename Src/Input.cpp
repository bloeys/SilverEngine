#include <SDL/SDL.h>
#include "Input.h"
#include "Time.h"

namespace Silver {

	size_t Input::m_keysPressed = 0;
	Input::MouseInfo Input::m_mouseInfo;
	std::vector<SDL_WindowEventID> Input::m_windowEvents = {};
	std::unordered_map <SDL_Keycode, Input::KeyInfo> Input::m_keys = {};
	std::unordered_map <std::string, Input::Button> Input::m_buttons = {};
	std::unordered_map <SDL_Keycode, Input::KeyInfo>::iterator Input::m_it = Input::m_keys.begin();

	void Input::Update()
	{
		for (m_it = m_keys.begin(); m_it != m_keys.end(); m_it++)
		{
			if (m_it->second.secondsSinceRelease <= 0.5f)
				m_it->second.secondsSinceRelease += Time::GetDt();

			m_it->second.pressedThisFrame = false;
		}

		for (size_t i = 0; i < 5; i++)
		{
			m_mouseInfo.mouseBtns[i].clicks = 0;
			m_mouseInfo.mouseBtns[i].pressedThisFrame = m_mouseInfo.mouseBtns[i].releasedThisFrame = false;
		}
		m_windowEvents.clear();

		SDL_Event ev;
		while (SDL_PollEvent(&ev))
		{
			switch (ev.type)
			{
				//Keyboard
			case SDL_KEYDOWN:
			{
				SDL_Keycode code = ev.key.keysym.sym;

				if (m_keys.find(code) == m_keys.end())
					m_keys[code] = KeyInfo();

				if (!m_keys[code].isPressed)
					m_keys[code].pressedThisFrame = true;

				m_keys[code].isPressed = true;
				m_keysPressed++;
			}
			break;

			//Mouse
			case SDL_KEYUP:
				m_keys[ev.key.keysym.sym].secondsSinceRelease = 0;
				m_keys[ev.key.keysym.sym].isPressed = false;
				m_keysPressed--;
				break;
			case SDL_MOUSEMOTION:
				m_mouseInfo.prevX = m_mouseInfo.x;
				m_mouseInfo.prevY = m_mouseInfo.y;
				m_mouseInfo.x = ev.button.x;
				m_mouseInfo.y = ev.button.y;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (!m_mouseInfo.mouseBtns[ev.button.button].isPressed)
					m_mouseInfo.mouseBtns[ev.button.button].pressedThisFrame = true;

				m_mouseInfo.mouseBtns[ev.button.button].clicks = ev.button.clicks;
				m_mouseInfo.mouseBtns[ev.button.button].isPressed = true;
				break;
			case SDL_MOUSEBUTTONUP:
				m_mouseInfo.mouseBtns[ev.button.button].releasedThisFrame = true;
				m_mouseInfo.mouseBtns[ev.button.button].isPressed = false;
				break;

				//Window
			case SDL_WINDOWEVENT:
				m_windowEvents.emplace_back((SDL_WindowEventID)ev.window.event);
				break;
			}
		}
	}

	bool Input::RegisterButton(const std::string &btnName, const SDL_Keycode* requiredKeys, const SDL_Keycode* requiredMods, const size_t keyCount, const size_t modCount)
	{
		if (keyCount == 0 || m_buttons.find(btnName) != m_buttons.end())
			return false;

		Button *b = new Button(btnName, requiredKeys, requiredMods, keyCount, modCount);
		m_buttons[btnName] = *b;
		return true;
	}

	void Input::UpdateButton(const std::string &btnName, const SDL_Keycode* requiredKeys, const SDL_Keycode* requiredMods, const size_t keyCount, const size_t modCount)
	{
		if (m_buttons.find(btnName) == m_buttons.end())
			return;

		m_buttons[btnName].UpdateKeys(requiredKeys, requiredMods, keyCount, modCount);
	}

	void Input::DeleteButton(const std::string &btnName)
	{
		if (m_buttons.find(btnName) != m_buttons.end())
			m_buttons.erase(btnName);
	}
}