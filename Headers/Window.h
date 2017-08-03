#pragma once

struct SDL_Window;

namespace Silver {
	class Window
	{
	private:
		SDL_Window* window;
		bool isClosed;
		int width, height;
		const char* title;

	private:
		void Init();
		void HandleWindowEvents();

	public:
		Window(const char* windowTitle, const int windowWidth, const int windowHeight);
		void Clear() const;
		void Update();
		inline const bool Closed() const { return isClosed; }
		inline int GetWidth() const { return width; }
		inline int GetHeight() const { return height; }
		~Window();
	};
}