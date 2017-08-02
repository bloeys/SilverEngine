#pragma once

#include <queue>
#include "Renderer2DBase.h"

namespace Silver {
	class Renderer2D : public Renderer2DBase
	{
	private:
		std::queue<const Renderable2D*> renderQueue;

	public:
		//Renderer2D();
		void Draw(const Renderable2D *r) override;
		void Flush() override;
		//~Renderer2D();
	};
}