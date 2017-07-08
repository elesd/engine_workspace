#include <stdafx.h>
#include <engine/video/RenderTarget.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/Texture.h>

namespace engine
{
	struct RenderTargetPrivate
	{
		std::unique_ptr<Texture> texture;
		RenderTargetPrivate(std::unique_ptr<Texture>&& texture)
			: texture(std::move(texture))
		{ }
	};

	RenderTarget::RenderTarget(std::unique_ptr<Texture> &&texture)
		: _members(new RenderTargetPrivate(std::move(texture)))
	{

	}

	RenderTarget::~RenderTarget()
	{
		delete _members;
		_members = nullptr;
	}

	const Texture* RenderTarget::getTexture() const
	{
		return _members->texture.get();
	}

	Texture* RenderTarget::getTexture()
	{
		return _members->texture.get();
	}
}