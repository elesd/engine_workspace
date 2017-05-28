#include <stdafx.h>
#include <engine/render/Render.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/render/PipelineRendererBase.h>
#include <engine/render/RenderContext.h>

namespace engine
{
	struct RenderPrivate
	{
		std::unique_ptr<PipelineRendererBase> pipelineRender;
		RenderContext* renderContext = nullptr;
		RenderPrivate(RenderContext* renderContext, std::unique_ptr<PipelineRendererBase>&& pipelineRenderer)
			: pipelineRender(std::move(pipelineRenderer))
			, renderContext(renderContext)
		{ }
	};

	Render::Render(RenderContext* renderContext, std::unique_ptr<PipelineRendererBase>&& pipelineRenderer)
		: _members(new RenderPrivate(renderContext, std::move(pipelineRenderer)))
	{

	}

	Render::~Render()
	{
		delete _members;
		_members = nullptr;
	}

	void Render::render()
	{
		_members->pipelineRender->render();
	}
}