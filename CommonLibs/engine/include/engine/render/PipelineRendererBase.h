#pragma once

#include <engine/render/PipelineRenderer.h>
#include <engine/render/RenderPass.h>
namespace engine
{
	class PipelineRendererBase
	{
	public:

		template<typename PIPELINE, size_t pipelineSize>
		static std::unique_ptr<PipelineRendererBase> createRenderer(const std::array<std::unique_ptr<RenderPass>, pipelineSize> &&passes);
	public:
		PipelineRendererBase() = default;
		virtual ~PipelineRendererBase() {}

		virtual void render() = 0;
	};

	template<typename PIPELINE, size_t pipelineSize>
	std::unique_ptr<PipelineRendererBase> PipelineRendererBase::createRenderer(const std::array<std::unique_ptr<RenderPass>, pipelineSize> &&passes)
	{
		RenderPassPipeline<PIPELINE, pipelineSize> pipeline(passes);
		std::unique_ptr<PipelineRendererBase> result(new PipelineRenderer<PIPELINE, pipelineSize>(pipeline));
		return result;
	}
}