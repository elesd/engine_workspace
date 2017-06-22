#include <stdafx.h>
#include <engine/video/winapi/TextureImpl.h>
///////////////////////////////////////////////////////////////////////////////


namespace engine
{
	namespace winapi
	{

		TextureImpl::TextureImpl(ID3D11Texture2D* textureToWrap)
			: Texture()
		{
			INACTIVE_MODULE_ERROR();
		}
		TextureImpl::TextureImpl(ID3D11Texture2D* textureToWrap, const TextureDescription& desc)
			: Texture(desc)
		{
			INACTIVE_MODULE_ERROR();
		}

		TextureImpl::TextureImpl(TextureImpl&& o)
			: Texture(std::move(o))
		{
			INACTIVE_MODULE_ERROR();
		}

		TextureImpl::~TextureImpl() 
		{
			INACTIVE_MODULE_ERROR();
		}

		TextureImpl& TextureImpl::operator=(TextureImpl&& o)
		{
			INACTIVE_MODULE_ERROR();
			return *this;
		}

		ID3D11Texture2D* TextureImpl::getTextureInterface()
		{
			INACTIVE_MODULE_ERROR();
			return nullptr;
		}

		void TextureImpl::destroy()
		{
			INACTIVE_MODULE_ERROR();
		}
	}
}
