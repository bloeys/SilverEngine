#include <iostream>
#include <SDL/SDL.h>
#include "Window.h"
#include "Input.h"
#include "Time.h"
#include "Shader.h"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "FloatBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

int main(int argc, char* args[])
{
	using namespace Silver;

	SDL_Init(SDL_INIT_VIDEO);
	Window w("Silver Engine", 960, 540);	//16:9 aspect ratio

	SDL_Keycode keys[] = { SDLK_SPACE };
	SDL_Keycode mods[] = { SDLK_LCTRL };
	Input::RegisterButton("Jump", keys, mods, 1, 1);

	float dt = 16.0f / 1000.0f;

	float verts[] =
	{
		-10.0f, -1.0f,  -0.0f,
		-10.0f,  1.0f,  -0.0f,
		 10.0f,  1.0f,  -0.0f,
		 10.0f, -1.0f,  -0.0f
	};

	GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

	GLfloat colors1[] =
	{
		0, 0, 0, 1,
		1, 0, 0, 1,
		1, 1, 0, 1,
		1, 1, 1, 1
	};

	GLfloat colors2[] =
	{
		1, 1, 1, 1,
		0, 1, 1, 1,
		0, 0, 1, 1,
		0, 0, 0, 1
	};

	IndexBuffer ibo(indices, 6);
	VertexArray vao1, vao2;

	vao1.AddFloatBuffer(new FloatBuffer(verts, 4 * 3, 3), 0);
	vao1.AddFloatBuffer(new FloatBuffer(colors1, 4 * 4, 4), 1);

	vao2.AddFloatBuffer(new FloatBuffer(verts, 4 * 3, 3), 0);
	vao2.AddFloatBuffer(new FloatBuffer(colors2, 4 * 4, 4), 1);

	Shader s(R"(c:\Users\omarm\Documents\Visual Studio 2017\Projects\C++\SilverEngine\SilverEngine\Shaders\Test.vert)",
		R"(c:\Users\omarm\Documents\Visual Studio 2017\Projects\C++\SilverEngine\SilverEngine\Shaders\Test.frag)");
	s.Enable();
	s.AddUniform("projectionMat");
	s.AddUniform("modelMat");
	s.SetUniform("projectionMat", glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, -1.0f));

	//Game loop
	while (!w.Closed())
	{
		Time::Update();
		Input::Update();

		w.Clear();

		vao1.Bind();
		ibo.Bind();
		s.SetUniform("modelMat", glm::rotate(glm::mat4(1), 0.0f, glm::vec3(0, 0, -1)));
		glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_SHORT, 0);
		ibo.UnBind();
		vao1.UnBind();

		vao2.Bind();
		ibo.Bind();
		s.SetUniform("modelMat", glm::rotate(glm::mat4(1), 90.0f, glm::vec3(0, 0, -1)));
		glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_SHORT, 0);
		ibo.UnBind();
		vao2.UnBind();

		w.Update();

		if (Input::IsButtonPressed("Jump"))
			std::cout << "Jumping!" << std::endl;
		if (Input::IsMousePressed(1))
			std::cout << "Mouse Left!" << std::endl;
		if (Input::IsMouseHeld(2))
			std::cout << "Mouse Middle!" << std::endl;
		if (Input::IsMouseReleased(3))
			std::cout << "Mouse Right!" << std::endl;
	}
	SDL_Quit();

	return 0;
}