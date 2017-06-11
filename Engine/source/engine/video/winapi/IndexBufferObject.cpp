#include <stdafx.h>
#include <engine/video/winapi/IndexBufferObject.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/winapi/DriverImpl.h>

#include <d3d11.h>

namespace
{
	D3D11_BUFFER_DESC createVertexBufferDescription(size_t size)
	{
		D3D11_BUFFER_DESC res = {0};
		res.Usage = D3D11_USAGE_DYNAMIC;
		res.ByteWidth = size;
		res.CPUAccessFlags = 0;
		res.BindFlags = D3D11_BIND_INDEX_BUFFER;
		return res;
	}
}

namespace engine
{
	namespace winapi
	{
		struct IndexBufferObjectPrivate
		{
			ID3D11Buffer* buffer = nullptr;
			std::unique_ptr<D3D11_MAPPED_SUBRESOURCE> bindResource;
			D3D11_BUFFER_DESC description;
			DriverImpl* driver = nullptr;
		};

		IndexBufferObject::IndexBufferObject(size_t size, Driver* driver)
		{
			_members->driver = static_cast<DriverImpl*>(driver);
			_members->description = createVertexBufferDescription(size);
		}

		IndexBufferObject::~IndexBufferObject()
		{
			if(_members)
			{
				if(_members->buffer)
				{
					_members->buffer->Release();
				}
				if(isBind())
				{
					unbind();
				}
			}
			delete _members;
			_members = nullptr;
		}

		void IndexBufferObject::bind()
		{
			_members->driver->bind(this);
		}

		void IndexBufferObject::unbind()
		{
			_members->driver->unbind(this);
		}

		void IndexBufferObject::setData(const char* data, size_t size)
		{
			ASSERT(isBind());
			memcpy(_members->bindResource.get(), data, size);
		}

		const D3D11_BUFFER_DESC& IndexBufferObject::getDescription() const
		{
			return _members->description;
		}

		ID3D11Buffer* IndexBufferObject::getBufferInterface() const
		{
			return _members->buffer;
		}

		D3D11_MAPPED_SUBRESOURCE* IndexBufferObject::getBindResource() const
		{
			return _members->bindResource.get();
		}
		
		bool IndexBufferObject::isBind() const
		{
			return getBindResource() != nullptr;
		}

		void IndexBufferObject::setBindResource(std::unique_ptr<D3D11_MAPPED_SUBRESOURCE>&& mapData)
		{
			_members->bindResource = std::move(mapData);
		}
	}
}