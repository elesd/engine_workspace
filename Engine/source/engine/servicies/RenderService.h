#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

#include <engine/render/RenderPass.h>
#include <engine/render/PipelineRendererBase.h>
#include <engine/render/RenderContext.h>

namespace engine
{
	class RenderContext;

	class RenderService final
		: private NonCopyable
		, private NonMoveable
	{
	public:
		explicit RenderService(RenderContext* renderContext);
		~RenderService();

		template<typename RenderPassEnum, uint32_t SizeOfEnum>
		void createRenderer(const std::string& rendererName, const std::array<std::string, SizeOfEnum>& renderPassNames);
		
	private:
		RenderContext* getRenderContext() const;

	private:
		struct RenderServicePrivate* _members = nullptr;
	};

	template<typename RenderPassEnum, uint32_t SizeOfEnum>
	void RenderService::createRenderer(const std::string& rendererName, const std::array<std::string, SizeOfEnum>& renderPassNames)
	{
		RenderContext* renderContext = getRenderContext();
		std::array<std::unique_ptr<engine::RenderPass>, SizeOfEnum> renderPasses;
		for(size_t i = 0; i < renderPassNames.size(); ++i)
		{
			renderPasses[i].reset(new RenderPass(renderPassNames[i], renderContext));
		}
		std::unique_ptr<engine::PipelineRendererBase> pipelineRenderer = engine::PipelineRendererBase::template createRenderer<RenderPassEnum, SizeOfEnum>(std::move(renderPasses));
		
		renderContext->createRenderer(rendererName, std::move(pipelineRenderer));
	}
}

