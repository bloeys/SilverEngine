#pragma once

#include <vector>
#include <glm/mat4x4.hpp>
#include "Shader.h"
#include "Renderer2DBase.h"
#include "Renderable2D.h"

namespace Silver {
	class LayerBase
	{
	protected:
		Renderer2DBase* renderer;
		std::vector<Renderable2D*>renderables;
		Shader* shader;
		glm::mat4 projectionMat;

	protected:
		LayerBase(Renderer2DBase*, Shader*, glm::mat4);

	public:
		virtual inline void Add(Renderable2D* r){ renderables.push_back(r); }
		virtual void Draw();
		virtual ~LayerBase();
	};
}