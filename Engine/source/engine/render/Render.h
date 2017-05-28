#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	class Driver;
	class PipelineRendererBase;

	class Render 
		: private NonCopyable
		, private NonMoveable
	{
	public:
		Render(RenderContext* renderContext, std::unique_ptr<PipelineRendererBase>&& pipelineRenderer);
		virtual ~Render();

		void render();
		// TODO:
		// SetViewPort
		// SetRenderTarget
	private:
		struct RenderPrivate* _members = nullptr;
	};
}