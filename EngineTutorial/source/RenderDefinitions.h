#include <engine/render/PipelineRenderer.h>

namespace engine
{
	class RenderContext;
}

#include <engine/render/RenderPass.h>
#include <engine/render/RenderContext.h>
#include <engine/render/PipelineRendererBase.h>

namespace renderPasses
{
	template<typename RenderPassEnum, uint32_t SizeOfEnum>
	struct GeneralDefinition
	{
		static std::unique_ptr<engine::PipelineRendererBase> createRenderer(engine::RenderContext* renderContext, const std::array<std::string, SizeOfEnum>& names)
		{
			std::unique_ptr<engine::PipelineRendererBase> result = engine::PipelineRendererBase::createRenderer<RenderPassEnum, SizeOfEnum>(createParam(renderContext, names));
			return result;
		}
		static std::array<std::unique_ptr<engine::RenderPass>, SizeOfEnum> createParam(engine::RenderContext* renderContext, const std::array<std::string, SizeOfEnum>& names)
		{
			std::array<std::unique_ptr<engine::RenderPass>, SizeOfEnum> result;
			for(size_t i = 0; i < names.size(); ++i)
			{
				result[i] = std::make_unique<engine::RenderPass>(names[i], renderContext);
			}
			return result;
		}

	};

	struct OnlySloid
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
