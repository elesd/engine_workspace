
namespace engine
{
	template<typename PIPELINE, size_t pipelineSize>
	PipelineRenderer<PIPELINE, pipelineSize>::PipelineRenderer(RenderPassPipeline<PIPELINE, pipelineSize> &&pipeline)
		: _pipeline(std::move(pipeline))
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

	template<typename PIPELINE, size_t pipelineSize>
	RenderPass* PipelineRenderer<PIPELINE, pipelineSize>::getRenderPass(PIPELINE pass)
	{
		return _pipeline.getRenderPass(pass);
	}

}

