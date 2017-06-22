#include <engine/render/PipelineRenderer.h>

namespace engine
{
	class RenderContext;
}

namespace renderPasses
{
	struct TutorialStep01
	{
		enum class Passes
		{
			Solid
		};
		using Pipeline = engine::RenderPassPipeline<Passes, 1>;
		using PipelineRenderer = engine::PipelineRenderer<Passes, 1>;

		static std::unique_ptr<engine::PipelineRendererBase> createRenderer(engine::RenderContext*);
		static std::array<std::unique_ptr<engine::RenderPass>, 1> createParam(engine::RenderContext*);
	};
	
}
