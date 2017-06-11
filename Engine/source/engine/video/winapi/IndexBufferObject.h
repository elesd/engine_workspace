#pragma once

#include <engine/video/BufferObject.h>

struct D3D11_BUFFER_DESC;
struct ID3D11Buffer;
struct D3D11_MAPPED_SUBRESOURCE;

namespace engine
{
	class Driver;
	namespace winapi
	{
		class IndexBufferObject
			: public BufferObject
		{
		public:
			IndexBufferObject(size_t size, Driver* driver);
			~IndexBufferObject() override;
			void bind() override;
			void unbind() override;
			void setData(const char* data, size_t size) override;

			const D3D11_BUFFER_DESC& getDescription() const;

			ID3D11Buffer* getBufferInterface() const;
			D3D11_MAPPED_SUBRESOURCE* getBindResource() const;
			bool isBind() const;
			void setBindResource(std::unique_ptr<D3D11_MAPPED_SUBRESOURCE>&& mapData);
		private:
			struct IndexBufferObjectPrivate* _members = nullptr;
		};
	}
}