#include <stdafx.h>
#include <engine/video/Texture.h>
///////////////////////////////////////////////////////////////////////////////

namespace engine
{
	struct TexturePrivate
	{
		TextureDescription description;
		bool hasValidDescription = false;
		TexturePrivate() = default;
		TexturePrivate(const TextureDescription& desc) : description(desc), hasValidDescription(true)
		{ }
	};

	Texture::Texture()
		: _members(new TexturePrivate())
	{

	}

	Texture::Texture(const TextureDescription& desc)
		: _members(new TexturePrivate(desc))
	{

	}

	Texture::Texture(Texture&& o)
		: _members(o._members)
	{
		o._members = nullptr;
	}

	Texture& Texture::operator=(Texture&& o)
	{
		delete _members;
		_members = o._members;
		o._members = nullptr;
		return *this;
	}
	
	Texture::~Texture()
	{
		delete _members;
		_members = nullptr;
	}


	const TextureDescription& Texture::getDescription() const
	{
		ASSERT(HasValidDescription());
		return _members->description;
	}

	bool Texture::HasValidDescription() const
	{
		return _members->hasValidDescription;
	}
}