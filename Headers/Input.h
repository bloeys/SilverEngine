#pragma once

#include <unordered_map>
#include <SDL/SDL_keycode.h>
#include <vector>
#include <string>

namespace Silver {
	class Input
	{
		struct KeyInfo
		{
			bool isPressed, pressedThisFrame, releasedThisFrame;
		};

		struct Button
		{
			std::string name;
			SDL_Keycode* btnKeys = nullptr;
			size_t keyCount;

			Button::Button() : name(""), btnKeys(nullptr), keyCount(0)
			{
			}

			Button::Button(const std::string &btnName, SDL_Keycode *requiredKeys, size_t count)
			{
				name = btnName;
				keyCount = count;
				UpdateKeys(requiredKeys, count);
			}

			void Button::UpdateKeys(SDL_Keycode *newKeys, size_t newCount)
			{
				if (btnKeys != nullptr)
					delete[] btnKeys;

				btnKeys = new SDL_Keycode[newCount];
				for (size_t i = 0; i < newCount; i++)
					btnKeys[i] = newKeys[i];
			}

			Button::~Button()
			{
				if (btnKeys != nullptr)
					delete[] btnKeys;
			}
		};

	private:
		static size_t keysPressed;
		static std::vector<SDL_WindowEventID> windowEvents;
		static std::unordered_map <SDL_Keycode, KeyInfo> keys;
		static std::unordered_map <std::string, Button> buttons;
		static std::unordered_map <SDL_Keycode, KeyInfo>::iterator it;

	public:
		static void Update();

		static inline bool AnyKeyDown() { return keysPressed; }

		//Returns Whether the key was pressed this frame
		static inline bool IsKeyPressed(SDL_Keycode key)
		{
			if (keys.find(key) == keys.end())
				return false;
			return keys[key].pressedThisFrame;
		}

		//Returns Whether the key is pressed
		static inline bool IsKeyHeld(SDL_Keycode key)
		{
			if (keys.find(key) == keys.end())
				return false;
			return keys[key].isPressed;
		}

		//Returns Whether the key was released this frame
		static inline bool IsKeyReleased(SDL_Keycode key)
		{
			if (keys.find(key) == keys.end())
				return false;
			return keys[key].releasedThisFrame;
		}

		//Returns Whether the key is not pressed
		static inline bool IsKeyUp(SDL_Keycode key)
		{
			if (keys.find(key) == keys.end())
				return true;
			return !keys[key].isPressed;
		}

		//Registers a named combination of keys that can be queried together. Returns 'True' if the registration was successful, and false if there is a name collision with another button.
		static bool RegisterButton(const std::string &btnName, SDL_Keycode* requiredKeys, size_t keyCount);

		//Returns Whether the button was pressed this frame
		static inline bool IsButtonPressed(const std::string &btnName)
		{
			if (buttons.find(btnName) == buttons.end())
				return false;

			for (size_t i = 0; i < buttons[btnName].keyCount; i++)
				if (!IsKeyPressed(buttons[btnName].btnKeys[i]))
					return false;

			return true;
		}

		//Returns Whether the button is pressed
		static inline bool IsButtonHeld(const std::string &btnName)
		{
			if (buttons.find(btnName) == buttons.end())
				return false;

			for (size_t i = 0; i < buttons[btnName].keyCount; i++)
				if (!IsKeyHeld(buttons[btnName].btnKeys[i]))
					return false;

			return true;
		}

		//Returns Whether the button was released this frame
		static inline bool IsButtonReleased(const std::string &btnName)
		{
			if (buttons.find(btnName) == buttons.end())
				return false;

			for (size_t i = 0; i < buttons[btnName].keyCount; i++)
				if (!IsKeyReleased(buttons[btnName].btnKeys[i]))
					return false;

			return true;
		}

		//Returns Whether the button is not pressed
		static inline bool IsButtonUp(const std::string &btnName)
		{
			if (buttons.find(btnName) == buttons.end())
				return false;

			for (size_t i = 0; i < buttons[btnName].keyCount; i++)
				if (!IsKeyUp(buttons[btnName].btnKeys[i]))
					return false;

			return true;
		}

		static void UpdateButton(const std::string &btnName, SDL_Keycode* requiredKeys, size_t keyCount);

		static void DeleteButton(const std::string &btnName);

		static inline const std::vector<SDL_WindowEventID> &GetCurrentWindowEvents() { return windowEvents; }
	};
}