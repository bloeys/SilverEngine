#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

namespace Silver {
	class Renderable2D
	{
	public:
		glm::vec3 pos;
		glm::vec2 size;
		glm::vec4 color;
		
	protected:
		Shader &shader;
		VertexArray *vao;
		IndexBuffer *ibo;

	protected:
		void Init();

	public:
		Renderable2D(glm::vec3 position, glm::vec2 size, Shader &shader);
		Renderable2D(glm::vec3 position, glm::vec2 size, glm::vec4 color, Shader &shader);
		~Renderable2D();

		inline const glm::vec3& GetPos()	const  { return pos; }
		inline const glm::vec2& GetScale()	const  { return size; }
		inline const glm::vec2& GetColor()	const  { return color; }
		
		inline const VertexArray* GetVAO()	const { return vao; }
		inline const IndexBuffer* GetIBO()	const { return ibo; }
		inline Shader& GetShader()	const { return shader; }
	};
}