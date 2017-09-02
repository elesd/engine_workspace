#include <stdafx.h>
#include <engine/video/winapi/IndexBufferObject.h>
///////////////////////////////////////////////////////////////////////////////

#if ENGINE_USE_WINAPI

#include <engine/video/winapi/DriverImpl.h>

#include <d3d11.h>

namespace
{
	D3D11_BUFFER_DESC createVertexBufferDescription(size_t size)
	{
		D3D11_BUFFER_DESC res = {0};
		res.Usage = D3D11_USAGE_DYNAMIC;
		res.ByteWidth = size;
		res.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
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
			D3D11_MAPPED_SUBRESOURCE bindResource;
			D3D11_BUFFER_DESC description;
			DriverImpl* driver = nullptr;
		};

		IndexBufferObject::IndexBufferObject(size_t size, Driver* driver)
			:_members(new IndexBufferObjectPrivate())
		{
			_members->driver = static_cast<DriverImpl*>(driver);
			_members->description = createVertexBufferDescription(size);
			_members->buffer = _members->driver->createBuffer(_members->description);
		}

		IndexBufferObject::~IndexBufferObject()
		{
			if(_members)
			{
				if(_members->buffer)
				{
					_members->buffer->Release();
				}
				if(isBound())
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
			ASSERT(isBound());
			memcpy(_members->bindResource.pData, data, size);
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
			return &_members->bindResource;
		}
		
		bool IndexBufferObject::isBound() const
		{
			return getBindResource()->pData != nullptr;
		}

		void IndexBufferObject::setBindResource(const D3D11_MAPPED_SUBRESOURCE& mapData)
		{
			_members->bindResource = mapData;
		}
	}
}


#endif