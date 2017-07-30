#pragma once

struct SDL_Window;

class Window
{
private:
	SDL_Window* m_window;
	bool m_isClosed;
	int m_width, m_height;
	const char* m_title;

private:
	void Init();
	void PollEvents();
	void HandleWindowEvents(Uint8 ev);

public:
	Window(const char* title, const int width, const int height);
	void Update();
	inline bool Closed() const { return m_isClosed; }
	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }
	~Window();
};