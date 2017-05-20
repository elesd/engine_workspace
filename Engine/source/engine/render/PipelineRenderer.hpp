
namespace engine
{
	template<typename PIPELINE, size_t pipelineSize>
	PipelineRenderer<PIPELINE, pipelineSize>::PipelineRenderer(RenderPassPipeline<PIPELINE, pipelineSize> &&pipeline)
		: pipeline(std::move(pipeline))
	{

	}

	template<typename PIPELINE, size_t pipelineSize>
	PipelineRenderer<PIPELINE, pipelineSize>::~PipelineRenderer()
	{

	}

	template<typename PIPELINE, size_t pipelineSize>
	void PipelineRenderer<PIPELINE, pipelineSize>::render()
	{
		for (auto it = _pipeline.begin(); it != _pipeline.end(); ++it)
		{
			it->render();
		}
	}
}

