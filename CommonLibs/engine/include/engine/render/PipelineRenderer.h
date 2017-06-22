#pragma once

#include <engine/render/RenderPassPipeline.h>
#include <engine/render/PipelineRendererBase.h>

namespace engine
{
	template<typename PIPELINE, size_t pipelineSize>
	class PipelineRenderer : public PipelineRendererBase
	{
	public:
		PipelineRenderer(RenderPassPipeline<PIPELINE, pipelineSize> &&pipeline);
		~PipelineRenderer();

		void render() override;

		RenderPass* getRenderPass(PIPELINE pass);
	private:
		RenderPassPipeline<PIPELINE, pipelineSize> _pipeline;
	};
}

#include <engine/render/PipelineRenderer.hpp>