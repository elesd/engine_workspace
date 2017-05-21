
namespace engine
{
	template<typename PIPELINE, size_t pipelineSize>
	RenderPassPipeline<PIPELINE, pipelineSize>::Iterator::Iterator(RenderPassPipeline &pipeline, size_t index)
		: _currentIndex(index)
		, _pipeline(pipeline)
	{

	}

	template<typename PIPELINE, size_t pipelineSize>
	RenderPassPipeline<PIPELINE, pipelineSize>::Iterator::Iterator(Iterator& o)
		: _currentIndex(o._currentIndex)
		, _pipeline(o._pipeline)
	{

	}

	template<typename PIPELINE, size_t pipelineSize>
	RenderPass& RenderPassPipeline<PIPELINE, pipelineSize>::Iterator::operator->() const
	{
		return *renderPass._pipeline[_currentIndex].get();
	}

	template<typename PIPELINE, size_t pipelineSize>
	typename RenderPassPipeline<PIPELINE, pipelineSize>::Iterator& RenderPassPipeline<PIPELINE, pipelineSize>::Iterator::operator++()
	{
		++_currentIndex;
		return *this;
	}

	template<typename PIPELINE, size_t pipelineSize>
	bool RenderPassPipeline<PIPELINE, pipelineSize>::Iterator::operator==(const typename RenderPassPipeline<PIPELINE, pipelineSize>::Iterator& o) const
	{
		ASSERT(_pipeline == o._pipeline);
		return _currentIndex == o._currentIndex;
	}

	///////////////////////////////////////////////////////////////////////////

	template<typename PIPELINE, size_t pipelineSize>
	RenderPassPipeline<PIPELINE, pipelineSize>::RenderPassPipeline(std::array<std::unique_ptr<RenderPass>, pipelineSize> &&pipeline)
	{

	}

	template<typename PIPELINE, size_t pipelineSize>
	RenderPassPipeline<PIPELINE, pipelineSize>::RenderPassPipeline(RenderPassPipeline &&o)
		: _pipeline(std::move(o._pipeline))
	{

	}

	template<typename PIPELINE, size_t pipelineSize>
	typename RenderPassPipeline<PIPELINE, pipelineSize>::Iterator RenderPassPipeline<PIPELINE, pipelineSize>::begin()
	{
		return Iterator(*this, 0);
	}

	template<typename PIPELINE, size_t pipelineSize>
	typename RenderPassPipeline<PIPELINE, pipelineSize>::Iterator RenderPassPipeline<PIPELINE, pipelineSize>::end()
	{
		return Iterator(*this, pipelineSize);
	}

	template<typename PIPELINE, size_t pipelineSize>
	RenderPass* RenderPassPipeline<PIPELINE, pipelineSize>::getRenderPass(PIPELINE pass)
	{
		size_t correspondingIndex = static_cast<size_t>(pass);
		ASSERT(correspondingIndex < pipelineSize);
		return _pipeline[correspondingIndex].get();
	}
}