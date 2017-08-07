#include <stdafx.h>
#include <RenderDefinitions.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/render/RenderPass.h>
#include <engine/render/PipelineRendererBase.h>

namespace renderPasses
{

	std::array<std::unique_ptr<engine::RenderPass>, 1> TutorialStep01::createParam(engine::RenderContext* renderContext)
	{
		return {std::make_unique<engine::RenderPass>("Solid", renderContext)};
	}

	std::unique_ptr<engine::PipelineRendererBase> TutorialStep01::createRenderer(engine::RenderContext* renderContext)
	{
		std::unique_ptr<engine::PipelineRendererBase> result = engine::PipelineRendererBase::createRenderer<Passes, 1>(createParam(renderContext));
		return result;
	}

	std::array<std::unique_ptr<engine::RenderPass>, 1> TutorialStep02::createParam(engine::RenderContext* renderContext)
	{
		return{std::make_unique<engine::RenderPass>("Solid", renderContext)};
	}

	std::unique_ptr<engine::PipelineRendererBase> TutorialStep02::createRenderer(engine::RenderContext* renderContext)
	{
		std::unique_ptr<engine::PipelineRendererBase> result = engine::PipelineRendererBase::createRenderer<Passes, 1>(createParam(renderContext));
		return result;
	}
}
