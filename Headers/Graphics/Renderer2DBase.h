#pragma once

#include "Renderable2D.h"

namespace Silver {
	class Renderer2DBase
	{
	public:
		virtual void BeginAdd() = 0;
		virtual void Add(const Renderable2D *r) = 0;
		virtual void Flush() = 0;
	};
}