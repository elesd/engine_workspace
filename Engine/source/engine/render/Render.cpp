#include <stdafx.h>
#include <engine/render/Render.h>

#include <engine/render/PipelineRendererBase.h>

namespace engine
{
	struct RenderPrivate
	{
		std::unique_ptr<PipelineRendererBase> pipelineRender;
		RenderPrivate(std::unique_ptr<PipelineRendererBase>&& pipelineRenderer)
			: pipelineRender(std::move(pipelineRenderer))
		{ }
	};

	Render::Render(std::unique_ptr<PipelineRendererBase>&& pipelineRenderer)
		: _members(new RenderPrivate(std::move(pipelineRenderer)))
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