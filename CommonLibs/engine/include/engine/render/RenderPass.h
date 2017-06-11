#pragma once

#include <engine/constraints/NonCopyable.h>

namespace engine
{
	class IRenderable;
	class RenderContext;

	class RenderPass 
		: private NonCopyable
	{
	public:
		RenderPass(const std::string& name, RenderContext* driver);
		RenderPass(RenderPass&&);
		RenderPass& operator=(RenderPass&&);

		virtual ~RenderPass();

		void render();

		void setClearColor(Color4 color);
		const Color4 &getClearColor() const;

		const std::vector<IRenderable*>& getObjects() const;
		std::vector<IRenderable*>& getObjects();
	private:
		struct RenderPassPrivate* _members = nullptr;
	};
}