#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	class Texture;
	class RenderTarget
		: private NonCopyable
		, private NonMoveable
	{
	public:
		RenderTarget(std::unique_ptr<Texture> &&texture);
		virtual ~RenderTarget();

		const Texture* getTexture() const;
	protected:
		Texture* getTexture();
	private:
		struct RenderTargetPrivate* _members = nullptr;
	};
}