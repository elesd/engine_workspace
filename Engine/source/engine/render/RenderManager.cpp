#include <stdafx.h>
#include <engine/render/RenderManager.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/render/Render.h>
#include <engine/render/RenderContext.h>

#include <engine/video/GlobalShaderResourceStorage.h>
namespace engine
{
	RenderManager::RenderManager()
	{

	}

	RenderManager::~RenderManager()
	{

	}

	void RenderManager::render(RenderContext* renderContext, std::vector<Render*> renders)
	{
		// TODO implement paralell rendering;
		for(Render* render: renders)
		{
			render->render();
		}
		renderContext->swapBuffer();
	}
}