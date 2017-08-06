#include "Graphics/MainLayer2D.h"
#include "Graphics/Renderer2D.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Silver {
	MainLayer2D::MainLayer2D(Renderer2DBase* rend, Shader* s, glm::mat4 projMatrix) : LayerBase(rend, s, projMatrix)
	{

	}
}