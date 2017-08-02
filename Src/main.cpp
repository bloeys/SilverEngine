#include <iostream>
#include <SDL/SDL.h>
#include "Window.h"
#include "Input.h"
#include "Time.h"
#include "Shader.h"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_VIDEO);
	Silver::Window w("Silver Engine", 960, 540);	//16:9 aspect ratio

	SDL_Keycode keys[] = { SDLK_SPACE };
	SDL_Keycode mods[] = { SDLK_LCTRL };
	Silver::Input::RegisterButton("Jump", keys, mods, 1, 1);

	float dt = 16.0f / 1000.0f;
	float verts[] = {
		-10.0f, -1.0f, -0.0f,
		-10.0f,  1.0f, -0.0f,
		 10.0f,  1.0f,  -0.0f,

		-10.0f, -1.0f, -0.0f,
		 10.0f,  1.0f,  -0.0f,
		 10.0f, -1.0f,  -0.0f
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	Silver::Shader s(R"(c:\Users\omarm\Documents\Visual Studio 2017\Projects\C++\SilverEngine\SilverEngine\Shaders\Test.vert)",
		R"(c:\Users\omarm\Documents\Visual Studio 2017\Projects\C++\SilverEngine\SilverEngine\Shaders\Test.frag)");
	s.Enable();
	s.AddUniform("projectionMat");
	s.AddUniform("modelMat");
	s.SetUniform("projectionMat", glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, -1.0f));
	s.SetUniform("modelMat", glm::rotate(glm::mat4(1), 45.0f, glm::vec3(0, 0, -1)));

	//Game loop
	while (!w.Closed())
	{
		Silver::Time::Update();
		Silver::Input::Update();

		w.Clear();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		w.Update();

		if (Silver::Input::IsButtonPressed("Jump"))
			std::cout << "Jumping!" << std::endl;
		if (Silver::Input::IsMousePressed(1))
			std::cout << "Mouse Left!" << std::endl;
		if (Silver::Input::IsMouseHeld(2))
			std::cout << "Mouse Middle!" << std::endl;
		if (Silver::Input::IsMouseReleased(3))
			std::cout << "Mouse Right!" << std::endl;
	}
	SDL_Quit();

	return 0;
}