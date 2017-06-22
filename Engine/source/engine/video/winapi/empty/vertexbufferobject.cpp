#include <stdafx.h>
#include <engine/video/winapi/VertexBufferObject.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/winapi/DriverImpl.h>

namespace engine
{
	namespace winapi
	{
	

		VertexBufferObject::VertexBufferObject(size_t size, Driver* driver)
		{
			INACTIVE_MODULE_ERROR();
		}

		VertexBufferObject::~VertexBufferObject() 
		{
			INACTIVE_MODULE_ERROR();
		}

		void VertexBufferObject::bind()
		{
			INACTIVE_MODULE_ERROR();
		}

		void VertexBufferObject::setData(const char* data, size_t size)
		{
			INACTIVE_MODULE_ERROR();
		}

		void VertexBufferObject::unbind()
		{
			INACTIVE_MODULE_ERROR();
		}

		const D3D11_BUFFER_DESC& VertexBufferObject::getDescription() const
		{
			INACTIVE_MODULE_ERROR();
			static D3D11_BUFFER_DESC result;
			return result;
		}

		ID3D11Buffer* VertexBufferObject::getBufferInterface() const
		{
			INACTIVE_MODULE_ERROR();
			return nullptr;
		}

		bool VertexBufferObject::isBind() const
		{
			INACTIVE_MODULE_ERROR();
			return false;
		}

		D3D11_MAPPED_SUBRESOURCE* VertexBufferObject::getBindResource() const
		{
			INACTIVE_MODULE_ERROR();
			return nullptr;
		}

		void VertexBufferObject::setBindResource(const D3D11_MAPPED_SUBRESOURCE& mapData)
		{
			INACTIVE_MODULE_ERROR();
		}
	}
}