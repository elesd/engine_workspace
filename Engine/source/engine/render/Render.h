#pragma once

#include <engine/constraints/NonCopyable.h>

namespace engine
{
	class Driver;
	class PipelineRendererBase;

	class Render final : private NonCopyable
	{
	public:
		Render(Driver *driver, std::unique_ptr<PipelineRendererBase>&& pipelineRenderer);
		~Render();

		void render();

	private:
		struct RenderPrivate* _members = nullptr;
	};
}