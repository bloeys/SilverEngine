#include <iostream>
#include <GL\glew.h>
#include <SDL\SDL.h>
#include "Window.h"

Window::Window(const char* title, const int width, const int height)
{
	m_title = title;
	m_width = width;
	m_height = height;
	Init();
}

void Window::Init()
{
	//Gl settings
	/*SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);*/
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//Window and opengl context for it
	m_window = SDL_CreateWindow(m_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	SDL_GL_CreateContext(m_window);

	//Start GLEW
	glewExperimental = GL_TRUE;
	GLenum msg = glewInit();
	if (msg != GLEW_OK)
	{
		std::cout << glewGetErrorString(msg);
		return;
	}
	std::cout << glGetString(GL_VERSION);

	glClearColor(0.3f, 0.7f, 0.3f, 1.0f);
}

void Window::Update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.0f, 0.5f);
	glVertex2f(0.5f, -0.5f);
	glEnd();

	PollEvents();
	SDL_GL_SwapWindow(m_window);	//Swap the back buffer
}

void Window::PollEvents()
{
	SDL_Event ev;
	while (SDL_PollEvent(&ev))
	{
		switch (ev.type)
		{
		case SDL_QUIT:
			m_isClosed = true;
			break;
		case SDL_KEYDOWN:
			if (ev.key.keysym.sym == SDLK_ESCAPE)
				m_isClosed = true;
			break;
		case SDL_WINDOWEVENT:
			HandleWindowEvents(ev.window.event);
			break;
		default:
			break;
		}
	}
}

void Window::HandleWindowEvents(Uint8 ev)
{
	switch (ev)
	{
	case SDL_WINDOWEVENT_RESIZED:
		SDL_GetWindowSize(m_window, &m_width, &m_height);	//Get new height and width
		glViewport(0, 0, m_width, m_height);	//Update the gl viewport to make sure elements stay in positions
		break;
	default:
		break;
	}
}

Window::~Window()
{
	SDL_DestroyWindow(m_window);
}