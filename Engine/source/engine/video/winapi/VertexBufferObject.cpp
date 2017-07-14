#include <stdafx.h>
#include <engine/video/winapi/VertexBufferObject.h>
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
		res.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		return res;
	}
}

namespace engine
{
	namespace winapi
	{
		struct VertexBufferObjectPrivate
		{
			ID3D11Buffer* buffer = nullptr;
			D3D11_MAPPED_SUBRESOURCE bindResource;
			D3D11_BUFFER_DESC description;
			DriverImpl* driver = nullptr;
		};

		VertexBufferObject::VertexBufferObject(size_t size, Driver* driver)
			: _members(new VertexBufferObjectPrivate())
		{
			_members->driver = static_cast<DriverImpl*>(driver);
			_members->description = createVertexBufferDescription(size);
			_members->buffer = _members->driver->createBuffer(_members->description);
		}

		VertexBufferObject::~VertexBufferObject() 
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

		void VertexBufferObject::bind()
		{
			_members->driver->bind(this);
		}

		void VertexBufferObject::setData(const char* data, size_t size)
		{
			ASSERT(isBound());
			memcpy(_members->bindResource.pData, data, size);
		}

		void VertexBufferObject::unbind()
		{
			_members->driver->unbind(this);
		}

		const D3D11_BUFFER_DESC& VertexBufferObject::getDescription() const
		{
			return _members->description;
		}

		ID3D11Buffer* VertexBufferObject::getBufferInterface() const
		{
			return _members->buffer;
		}

		bool VertexBufferObject::isBound() const
		{
			return getBindResource() != nullptr;
		}

		D3D11_MAPPED_SUBRESOURCE* VertexBufferObject::getBindResource() const
		{
			return &_members->bindResource;
		}

		void VertexBufferObject::setBindResource(const D3D11_MAPPED_SUBRESOURCE& mapData)
		{
			_members->bindResource = mapData;
		}
	}
}

#else

#include <engine/video/winapi/empty/VertexBufferObject.cpp>

#endif