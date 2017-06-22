#pragma once

#include <memory>
#include <engine/render/RenderPass.h>
namespace engine
{
	class PipelineRendererBase
	{
	public:

		template<typename PIPELINE, size_t pipelineSize>
		static std::unique_ptr<PipelineRendererBase> createRenderer(std::array<std::unique_ptr<RenderPass>, pipelineSize> &&passes);
	public:
		PipelineRendererBase() = default;
		virtual ~PipelineRendererBase() {}

		virtual void render() = 0;
	};
}

#include <engine/render/PipelineRenderer.h>

namespace engine
{
	template<typename PIPELINE, size_t pipelineSize>
	std::unique_ptr<PipelineRendererBase> PipelineRendererBase::createRenderer(std::array<std::unique_ptr<RenderPass>, pipelineSize> &&passes)
	{
		RenderPassPipeline<PIPELINE, pipelineSize> pipeline(std::move(passes));
		std::unique_ptr<PipelineRendererBase> result(new PipelineRenderer<PIPELINE, pipelineSize>(std::move(pipeline)));
		return result;
	}
}