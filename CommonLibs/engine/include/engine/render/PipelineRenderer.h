#pragma once

#include <engine/render/RenderPassPipeline.h>

namespace engine
{
	template<typename PIPELINE, size_t pipelineSize>
	class PipelineRenderer
	{
	public:
		PipelineRenderer(RenderPassPipeline<PIPELINE, pipelineSize> &&pipeline);
		~PipelineRenderer();

		void render() override;
	private:
		RenderPassPipeline<PIPELINE, pipelineSize> pipeline;
	};
}

#include <engine/render/PipelineRenderer.hpp>