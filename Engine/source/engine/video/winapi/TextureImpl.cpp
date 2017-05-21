#include <stdafx.h>
#include <engine/video/winapi/TextureImpl.h>
///////////////////////////////////////////////////////////////////////////////

#include <d3d11.h>

namespace engine
{
	namespace winapi
	{
		struct TextureImplPrivate
		{
			ID3D11Texture2D* texture = nullptr;
			TextureImplPrivate() = default;
			TextureImplPrivate(ID3D11Texture2D* textureToWrap): texture(textureToWrap)
			{ }
		};

		TextureImpl::TextureImpl(ID3D11Texture2D* textureToWrap)
			: Texture()
			, _members(new TextureImplPrivate(textureToWrap))
		{

		}
		TextureImpl::TextureImpl(ID3D11Texture2D* textureToWrap, const TextureDescription& desc)
			: Texture(desc)
			, _members(new TextureImplPrivate(textureToWrap))
		{
		}

		TextureImpl::TextureImpl(TextureImpl&& o)
			: Texture(std::move(o))
			, _members(o._members)
		{
			o._members = nullptr;
		}

		TextureImpl::~TextureImpl() 
		{
			destroy();
		}

		TextureImpl& TextureImpl::operator=(TextureImpl&& o)
		{
			Texture::operator=(std::move(o));
			destroy();
			_members = o._members;
			o._members = nullptr;
			return *this;
		}

		ID3D11Texture2D* TextureImpl::getTextureInterface()
		{
			return _members->texture;
		}

		void TextureImpl::destroy()
		{
			if(_members && _members->texture)
			{
				_members->texture->Release();
			}
			delete _members;
			_members = nullptr;
		}
	}
}
