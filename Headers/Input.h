#pragma once

#include <unordered_map>
#include <SDL/SDL_keycode.h>

namespace Silver {
	class Input
	{
		struct MouseInfo
		{
			struct MouseBtnInfo
			{
				unsigned char clicks = 0;	//1 is normal click, 2 is double click
				bool isPressed, pressedThisFrame,releasedThisFrame;
			};

			MouseBtnInfo *mouseBtns;
			int x, y, prevX, prevY;

			MouseInfo::MouseInfo()
			{
				mouseBtns = new MouseBtnInfo[5];
				for (size_t i = 0; i < 5; i++)
				{
					MouseBtnInfo *mbi = new MouseBtnInfo();
					mouseBtns[i] = *mbi;
				}
			}

			MouseInfo::~MouseInfo()
			{
				delete[] mouseBtns;
			}
		};

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

			Button::Button(const std::string &btnName, const SDL_Keycode *requiredKeys, const SDL_Keycode *newMods, const size_t newKeyCount, const size_t newModCount)
			{
				name = btnName;
				UpdateKeys(requiredKeys, newMods, newKeyCount, newModCount);
			}

			void Button::UpdateKeys(const SDL_Keycode *newKeys, const SDL_Keycode *newMods, const size_t newKeyCount, const size_t newModCount)
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
		static size_t m_keysPressed;
		static MouseInfo m_mouseInfo;
		static std::vector<SDL_WindowEventID> m_windowEvents;
		static std::unordered_map <SDL_Keycode, KeyInfo> m_keys;
		static std::unordered_map <std::string, Button> m_buttons;
		static std::unordered_map <SDL_Keycode, KeyInfo>::iterator m_it;

	public:
		static void Update();

#pragma region Keys
		static inline bool AnyKeyDown() { return m_keysPressed; }

		//Returns Whether the key was pressed this frame
		static inline bool IsKeyPressed(SDL_Keycode key)
		{
			if (m_keys.find(key) == m_keys.end())
				return false;
			return m_keys[key].pressedThisFrame;
		}

		//Returns Whether the key is pressed
		static inline bool IsKeyHeld(SDL_Keycode key)
		{
			if (m_keys.find(key) == m_keys.end())
				return false;
			return m_keys[key].isPressed;
		}

		//Returns Whether the key was released this frame
		static inline bool IsKeyReleased(SDL_Keycode key)
		{
			if (m_keys.find(key) == m_keys.end())
				return false;
			return m_keys[key].secondsSinceRelease == 0;
		}

		//Returns Whether the key is not pressed
		static inline bool IsKeyUp(SDL_Keycode key)
		{
			if (m_keys.find(key) == m_keys.end())
				return true;
			return !m_keys[key].isPressed;
		}
#pragma endregion

#pragma region Btns
		//Registers a named combination of keys that can be queried together.
		//TRUE if the registration was successful. FALSE if there is a name collision with another button or keyCount is ZERO .
		static bool RegisterButton(const std::string &btnName, const SDL_Keycode* requiredKeys, const SDL_Keycode* requiredMods, const size_t keyCount, const size_t modCount);

		//Returns Whether the button was pressed this frame
		static inline bool IsButtonPressed(const std::string &btnName)
		{
			if (m_buttons.find(btnName) == m_buttons.end())
				return false;

			for (size_t i = 0; i < m_buttons[btnName].keyCount; i++)
				if (!IsKeyPressed(m_buttons[btnName].btnKeys[i]))
					return false;
			for (size_t i = 0; i < m_buttons[btnName].modCount; i++)
				if (!IsKeyHeld(m_buttons[btnName].btnMods[i]))
					return false;

			return true;
		}

		//Returns Whether the button is pressed
		static inline bool IsButtonHeld(const std::string &btnName)
		{
			if (m_buttons.find(btnName) == m_buttons.end())
				return false;

			for (size_t i = 0; i < m_buttons[btnName].keyCount; i++)
				if (!IsKeyHeld(m_buttons[btnName].btnKeys[i]))
					return false;
			for (size_t i = 0; i < m_buttons[btnName].modCount; i++)
				if (!IsKeyHeld(m_buttons[btnName].btnMods[i]))
					return false;

			return true;
		}

		//Returns Whether the button was released this frame
		static inline bool IsButtonReleased(const std::string &btnName)
		{
			if (m_buttons.find(btnName) == m_buttons.end())
				return false;

			for (size_t i = 0; i < m_buttons[btnName].keyCount; i++)
				if (!IsKeyReleased(m_buttons[btnName].btnKeys[i]))
					return false;
			for (size_t i = 0; i < m_buttons[btnName].modCount; i++)
				if (m_keys[m_buttons[btnName].btnMods[i]].secondsSinceRelease > 0.5f)
					return false;

			return true;
		}

		//Returns Whether the button is not pressed
		static inline bool IsButtonUp(const std::string &btnName)
		{
			if (m_buttons.find(btnName) == m_buttons.end())
				return false;

			for (size_t i = 0; i < m_buttons[btnName].keyCount; i++)
				if (!IsKeyUp(m_buttons[btnName].btnKeys[i]))
					return false;
			for (size_t i = 0; i < m_buttons[btnName].modCount; i++)
				if (!IsKeyUp(m_buttons[btnName].btnMods[i]))
					return false;

			return true;
		}

		static void UpdateButton(const std::string &btnName, const SDL_Keycode* requiredKeys, const SDL_Keycode* requiredMods, const size_t keyCount, const size_t modCount);

		static void DeleteButton(const std::string &btnName);
#pragma endregion

#pragma region Mouse
		//From 0->4. 1: Left Mouse Btn. 2: Middle Mouse Btn. 3: Right Mouse Btn
		static inline bool IsMousePressed(const unsigned char index)
		{
			if (index > 4)
				return false;
			return m_mouseInfo.mouseBtns[index].pressedThisFrame;
		}

		static inline bool IsMouseDoubleClicked(const unsigned char index)
		{
			if (index > 4)
				return false;
			return m_mouseInfo.mouseBtns[index].clicks == 2;
		}

		static inline bool IsMouseHeld(const unsigned char index)
		{
			if (index > 4)
				return false;
			return m_mouseInfo.mouseBtns[index].isPressed;
		}

		static inline bool IsMouseReleased(const unsigned char index)
		{
			if (index > 4)
				return false;
			return m_mouseInfo.mouseBtns[index].releasedThisFrame;
		}

		static inline bool IsMouseUp(const unsigned char index)
		{
			if (index > 4)
				return false;
			return !m_mouseInfo.mouseBtns[index].isPressed;
		}
		
		//Current mouse X
		static const inline int GetMouseX() { return m_mouseInfo.x; }
		//Current mouse Y
		static const inline int GetMouseY() { return m_mouseInfo.y; }
		
		//Last Mouse X
		static const inline int GetPrevMouseX() { return m_mouseInfo.prevX; }
		//Last Mouse Y
		static const inline int GetPrevMouseY() { return m_mouseInfo.prevY; }
#pragma endregion


		static inline const std::vector<SDL_WindowEventID> &GetCurrentWindowEvents() { return m_windowEvents; }
	};
}