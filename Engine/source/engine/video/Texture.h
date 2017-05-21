#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/video/BufferDesc.h>

namespace engine
{
	struct BufferDesc;
	struct TextureDescription
	{
		int32_t width;
		int32_t height;
		int32_t mipMapCount;
		BufferDesc bufferDescription;
	};
	class Texture
		: private NonCopyable
	{
	protected:
		Texture();
		Texture(const TextureDescription& desc);
	public:
		Texture(Texture&&);
		Texture& operator=(Texture&&);
		virtual ~Texture();

		const TextureDescription& getDescription() const;
		bool HasValidDescription() const;
	protected:
	private:
		struct TexturePrivate* _members = nullptr;
	};
}