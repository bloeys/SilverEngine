#pragma once

#include "LayerBase.h"

namespace Silver {
	class MainLayer2D : public LayerBase
	{
	public:
		MainLayer2D(Renderer2DBase*, Shader*, glm::mat4);
	};
}