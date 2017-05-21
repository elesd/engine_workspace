#pragma once

#include <engine/constraints/NonCopyable.h>

namespace engine
{
	class IRenderable;
	class Driver;

	class RenderPass 
		: private NonCopyable
	{
	public:
		RenderPass(const std::string& name, Driver *driver);
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