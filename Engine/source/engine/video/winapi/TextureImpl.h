#pragma once

#include <engine/video/Texture.h>

struct ID3D11Texture2D;

namespace engine
{
	namespace winapi
	{
		class DriverImpl;

		class TextureImpl
			: public Texture
		{
		public:
			TextureImpl(ID3D11Texture2D* textureToWrap);
			TextureImpl(ID3D11Texture2D* textureToWrap, const TextureDescription& desc);
			TextureImpl(TextureImpl&& o);
			~TextureImpl() override;

			TextureImpl& operator=(TextureImpl&& o);

			ID3D11Texture2D* getTextureInterface();
		private:
			void destroy();
		private:
			struct TextureImplPrivate* _members = nullptr;
		};
	}
}