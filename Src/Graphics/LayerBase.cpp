#include "Graphics/LayerBase.h"

namespace Silver {
	LayerBase::LayerBase(Renderer2DBase* rend, Shader* s, glm::mat4 projMatrix)
		: renderer(rend), shader(s), projectionMat(projMatrix)
	{
		shader->Enable();
		shader->SetUniform("projectionMat", projectionMat);
		shader->Disable();
	}

	void LayerBase::Draw()
	{
		shader->Enable();
		renderer->BeginAdd();
		for (size_t i = 0; i < renderables.size(); i++)
			renderer->Add(renderables[i]);

		renderer->Flush();
	}

	LayerBase::~LayerBase()
	{
		delete shader;

		for (size_t i = 0; i < renderables.size(); i++)
			delete renderables[i];
	}
}