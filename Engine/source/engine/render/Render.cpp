#include <stdafx.h>
#include <engine/render/Render.h>

#include <engine/render/PipelineRendererBase.h>

namespace engine
{
	struct RenderPrivate
	{
		std::unique_ptr<PipelineRendererBase> pipelineRender;
		Driver *driver = nullptr;
		RenderPrivate(Driver* driver, std::unique_ptr<PipelineRendererBase>&& pipelineRenderer)
			: pipelineRender(std::move(pipelineRenderer))
			, driver(driver)
		{ }
	};

	Render::Render(Driver* driver, std::unique_ptr<PipelineRendererBase>&& pipelineRenderer)
		: _members(new RenderPrivate(driver, std::move(pipelineRenderer)))
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