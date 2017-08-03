#include <iostream>
#include <GL/glew.h>
#include <SDL/SDL.h>
#include "Window.h"
#include "Input.h"

namespace Silver {
	Window::Window(const char* windowTitle, const int windowWidth, const int windowHeight)
	{
		title = windowTitle;
		width = windowWidth;
		height = windowHeight;
		Init();
	}

	void Window::Init()
	{
		//SDL GL settings
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		//Window and opengl context for it
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

		if (window == NULL)
		{
			std::cout << "Window creation failed!" << std::endl;
			return;
		}
		SDL_GL_CreateContext(window);

		//Start GLEW
		glewExperimental = GL_TRUE;
		GLenum msg = glewInit();
		if (msg != GLEW_OK)
		{
			std::cout << glewGetErrorString(msg);
			return;
		}

		//GL settings
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CW);
		glClearColor(0.3f, 0.7f, 0.3f, 1.0f);

		std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;
	}

	void Window::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::Update()
	{
		if (Input::IsKeyPressed(SDLK_ESCAPE))
			isClosed = true;

		HandleWindowEvents();
		SDL_GL_SwapWindow(window);	//Swap the back buffer
	}

	void Window::HandleWindowEvents()
	{
		std::vector<SDL_WindowEventID> events = Input::GetCurrentWindowEvents();

		for (size_t i = 0; i < events.size(); i++)
		{
			if (events[i] == SDL_WINDOWEVENT_RESIZED)
			{
				SDL_GetWindowSize(window, &width, &height);	//Get new height and width
				glViewport(0, 0, width, height);	//Update the gl viewport to make sure elements stay in positions
			}
			else if (events[i] == SDL_WINDOWEVENT_CLOSE)
				isClosed = true;
		}
	}

	Window::~Window()
	{
		SDL_DestroyWindow(window);
	}
}