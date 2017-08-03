#pragma once

#include "Renderable2D.h"
#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

namespace Silver {
	class StaticSprite : public Renderable2D
	{
	protected:
		Shader &shader;
		VertexArray *vao;
		IndexBuffer *ibo;

	protected:
		void Init();

	public:
		StaticSprite(float x, float y, float width, float height, float r, float g, float b, float a, Shader &shader);
		StaticSprite(float x, float y, float width, float height, glm::vec4 col, Shader &shader);
		StaticSprite(glm::vec3 position, glm::vec2 size, Shader &shader);
		StaticSprite(glm::vec3 position, glm::vec2 size, glm::vec4 color, Shader &shader);
		~StaticSprite();

		inline const VertexArray* GetVAO()	const { return vao; }
		inline const IndexBuffer* GetIBO()	const { return ibo; }
		inline Shader& GetShader()	const { return shader; }
	};
}