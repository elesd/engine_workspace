#pragma once

#include <engine/constraints/NonCopyable.h>

namespace engine
{
	class Driver;
	class PipelineRendererBase;

	class Render final : private NonCopyable
	{
	public:
		// TODO Add RenderContext instead of driver
		Render(Driver *driver, std::unique_ptr<PipelineRendererBase>&& pipelineRenderer);
		~Render();

		void render();
		// TODO:
		// SetViewPort
		// SetRenderTarget
	private:
		struct RenderPrivate* _members = nullptr;
	};
}