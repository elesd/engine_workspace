#pragma once

#include <engine/render/RenderPass.h>

namespace engine
{
	class RenderPass;

	template<typename PIPELINE, size_t pipelineSize>
	class RenderPassPipeline
	{
		class Iterator
		{
			friend class RenderPassPipeline;
		private:
			Iterator(RenderPassPipeline &pipeline, size_t index);
		public:
			Iterator(Iterator&);
			RenderPass& operator->() const;
			Iterator& operator++();
			bool operator==(const Iterator& o) const;
		private:
			size_t _currentIndex = 0;
			RenderPassPipeline &pipeline;
		};

	public:
		explicit RenderPassPipeline(std::array<std::unique_ptr<RenderPass>, pipelineSize> &&pipeline);
		RenderPassPipeline(RenderPassPipeline&&);

		Iterator begin();
		Iterator end();
		
		RenderPass* getRenderPass(PIPELINE pass);
	private:
		std::array<std::unique_ptr<RenderPass>, pipelineSize> _pipeline;
	};
}

#include <engine/render/RenderPassPipeline.hpp>