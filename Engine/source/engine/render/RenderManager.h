#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	class RenderContext;
	class Renderer;

	class RenderManager final
		: private NonCopyable
		, private NonMoveable
	{
		friend class Application;
	private:
		RenderManager();
	public:
		~RenderManager();

		void render(RenderContext* renderContext, std::vector<Renderer*> renders);
	};
}