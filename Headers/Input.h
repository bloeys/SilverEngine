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
			float secondsSinceRelease = 1;
			bool isPressed, pressedThisFrame;
		};

		struct Button
		{
			std::string name;
			SDL_Keycode *btnKeys = nullptr, *btnMods = nullptr;
			size_t keyCount, modCount;

			Button::Button() : name(""), btnKeys(nullptr), btnMods(nullptr), keyCount(0), modCount(0)
			{
			}

			Button::Button(const std::string &btnName, SDL_Keycode *requiredKeys, SDL_Keycode *newMods, size_t newKeyCount, size_t newModCount)
			{
				name = btnName;
				UpdateKeys(requiredKeys, newMods, newKeyCount, newModCount);
			}

			void Button::UpdateKeys(SDL_Keycode *newKeys, SDL_Keycode *newMods, size_t newKeyCount, size_t newModCount)
			{
				if (btnKeys != nullptr)
					delete[] btnKeys;
				if (btnMods != nullptr)
					delete[] btnMods;

				keyCount = newKeyCount;
				modCount = newModCount;

				btnKeys = new SDL_Keycode[newKeyCount];
				for (size_t i = 0; i < newKeyCount; i++)
					btnKeys[i] = newKeys[i];

				if (modCount == 0)
				{
					btnMods = nullptr;
					return;
				}

				btnMods = new SDL_Keycode[modCount];
				for (size_t i = 0; i < newModCount; i++)
					btnMods[i] = newMods[i];
			}

			Button::~Button()
			{
				if (btnKeys != nullptr)
					delete[] btnKeys;
				if (btnMods != nullptr)
					delete[] btnMods;
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
			return keys[key].secondsSinceRelease == 0;
		}

		//Returns Whether the key is not pressed
		static inline bool IsKeyUp(SDL_Keycode key)
		{
			if (keys.find(key) == keys.end())
				return true;
			return !keys[key].isPressed;
		}

		//Registers a named combination of keys that can be queried together.
		//TRUE if the registration was successful. FALSE if there is a name collision with another button or keyCount is ZERO .
		static bool RegisterButton(const std::string &btnName, SDL_Keycode* requiredKeys, SDL_Keycode* requiredMods, size_t keyCount, size_t modCount);

		//Returns Whether the button was pressed this frame
		static inline bool IsButtonPressed(const std::string &btnName)
		{
			if (buttons.find(btnName) == buttons.end())
				return false;

			for (size_t i = 0; i < buttons[btnName].keyCount; i++)
				if (!IsKeyPressed(buttons[btnName].btnKeys[i]))
					return false;
			for (size_t i = 0; i < buttons[btnName].modCount; i++)
				if (!IsKeyHeld(buttons[btnName].btnMods[i]))
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
			for (size_t i = 0; i < buttons[btnName].modCount; i++)
				if (!IsKeyHeld(buttons[btnName].btnMods[i]))
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
			for (size_t i = 0; i < buttons[btnName].modCount; i++)
				if (keys[buttons[btnName].btnMods[i]].secondsSinceRelease > 0.5f)
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
			for (size_t i = 0; i < buttons[btnName].modCount; i++)
				if (!IsKeyUp(buttons[btnName].btnMods[i]))
					return false;

			return true;
		}

		static void UpdateButton(const std::string &btnName, SDL_Keycode* requiredKeys, SDL_Keycode* requiredMods, size_t keyCount, size_t modCount);

		static void DeleteButton(const std::string &btnName);

		static inline const std::vector<SDL_WindowEventID> &GetCurrentWindowEvents() { return windowEvents; }
	};
}