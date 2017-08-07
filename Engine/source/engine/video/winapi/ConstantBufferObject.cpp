#include <stdafx.h>
#include <engine/video/winapi/ConstantBufferObject.h>
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
		res.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		return res;
	}
}

namespace engine
{
	namespace winapi
	{
		struct ConstantBufferObjectPrivate
		{
			ID3D11Buffer* buffer = nullptr;
			D3D11_MAPPED_SUBRESOURCE bindResource;
			D3D11_BUFFER_DESC description;
			DriverImpl* driver = nullptr;
		};

		ConstantBufferObject::ConstantBufferObject(size_t size, Driver* driver)
			: _members(new ConstantBufferObjectPrivate())
		{
			_members->driver = static_cast<DriverImpl*>(driver);
			_members->description = createVertexBufferDescription(size);
			_members->buffer = _members->driver->createBuffer(_members->description);
		}

		ConstantBufferObject::ConstantBufferObject(ConstantBufferObject&& o)
			: _members(o._members)
		{
			o._members = nullptr;
		}

		ConstantBufferObject::~ConstantBufferObject()
		{
			if(_members)
			{
				if(isBound())
				{
					unbind();
				}
				if(_members->buffer)
				{
					_members->buffer->Release();
				}
			}
			delete _members;
			_members = nullptr;
		}

		ConstantBufferObject& ConstantBufferObject::operator=(ConstantBufferObject&& o)
		{
			delete _members;
			_members = o._members;
			o._members = nullptr;
			return *this;
		}

		void ConstantBufferObject::bind()
		{
			_members->driver->bind(this);
		}

		void ConstantBufferObject::setData(const char* data, size_t size)
		{
			ASSERT(isBound());
			memcpy(_members->bindResource.pData, data, size);
		}

		void ConstantBufferObject::unbind()
		{
			_members->driver->unbind(this);
		}

		const D3D11_BUFFER_DESC& ConstantBufferObject::getDescription() const
		{
			return _members->description;
		}

		ID3D11Buffer* ConstantBufferObject::getBufferInterface() const
		{
			return _members->buffer;
		}

		bool ConstantBufferObject::isBound() const
		{
			return getBindResource()->pData != nullptr;
		}

		D3D11_MAPPED_SUBRESOURCE* ConstantBufferObject::getBindResource() const
		{
			return &_members->bindResource;
		}

		void ConstantBufferObject::setBindResource(const D3D11_MAPPED_SUBRESOURCE& mapData)
		{
			_members->bindResource = mapData;
		}
	}
}

#else


#endif