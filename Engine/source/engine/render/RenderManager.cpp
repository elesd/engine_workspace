#include <stdafx.h>
#include <engine/render/RenderManager.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/render/Renderer.h>
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

	void RenderManager::render(RenderContext* renderContext, std::vector<Renderer*> renders)
	{
		// TODO implement paralell rendering;
		for(Renderer* render: renders)
		{
			render->render();
		}
		renderContext->swapBuffer();
	}
}