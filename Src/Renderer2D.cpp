#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer2D.h"

namespace Silver {
	void Renderer2D::Draw(const Renderable2D *r)
	{
		renderQueue.push(r);
	}

	void Renderer2D::Flush()
	{
		while (!renderQueue.empty())
		{
			const Renderable2D *r = renderQueue.front();
			r->GetVAO()->Bind();
			r->GetIBO()->Bind();

			r->GetShader().Enable();
			r->GetShader().SetUniform("modelMat", glm::translate(glm::mat4(1), r->GetPos()));
			glDrawElements(GL_TRIANGLES, r->GetIBO()->GetCount(), GL_UNSIGNED_SHORT, NULL);
			r->GetShader().Disable();

			r->GetIBO()->UnBind();
			r->GetVAO()->UnBind();
			renderQueue.pop();
		}
	}
}