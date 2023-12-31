#include <stdafx.h>
#include <RenderDefinitions.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/render/RenderPass.h>
#include <engine/render/RenderContext.h>
#include <engine/render/PipelineRendererBase.h>

namespace renderPasses
{

	std::array<std::unique_ptr<engine::RenderPass>, 1> OnlySloid::createParam(engine::RenderContext* renderContext)
	{
		return {std::make_unique<engine::RenderPass>("Solid", renderContext)};
	}

	std::unique_ptr<engine::PipelineRendererBase> OnlySloid::createRenderer(engine::RenderContext* renderContext)
	{
		std::unique_ptr<engine::PipelineRendererBase> result = engine::PipelineRendererBase::createRenderer<Passes, 1>(createParam(renderContext));
		return result;
	}


}
