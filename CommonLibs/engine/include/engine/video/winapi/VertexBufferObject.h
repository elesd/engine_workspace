#pragma once

#include <engine/video/BufferObject.h>

struct D3D11_BUFFER_DESC;
struct ID3D11Buffer;
struct D3D11_MAPPED_SUBRESOURCE;

namespace engine
{
	namespace winapi
	{
		class VertexBufferObject
			: public BufferObject
		{
		public:
			VertexBufferObject(size_t size, Driver* driver);
			~VertexBufferObject() override;

			void bind() override;
			void unbind() override;
			void setData(const char* data, size_t size) override;

			const D3D11_BUFFER_DESC& getDescription() const;

			ID3D11Buffer* getBufferInterface() const;
			D3D11_MAPPED_SUBRESOURCE* getBindResource() const;
			bool isBound() const;
			void setBindResource(const D3D11_MAPPED_SUBRESOURCE& mapData);
		private:
			struct VertexBufferObjectPrivate* _members = nullptr;
		};
	}
}