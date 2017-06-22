#include <stdafx.h>
#include <engine/video/winapi/IndexBufferObject.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/winapi/DriverImpl.h>


namespace engine
{
	namespace winapi
	{

		IndexBufferObject::IndexBufferObject(size_t size, Driver* driver)
		{
			INACTIVE_MODULE_ERROR();
		}

		IndexBufferObject::~IndexBufferObject()
		{
			INACTIVE_MODULE_ERROR();
		}

		void IndexBufferObject::bind()
		{
			INACTIVE_MODULE_ERROR();
		}

		void IndexBufferObject::unbind()
		{
			INACTIVE_MODULE_ERROR();
		}

		void IndexBufferObject::setData(const char* data, size_t size)
		{
			INACTIVE_MODULE_ERROR();
		}

		const D3D11_BUFFER_DESC& IndexBufferObject::getDescription() const
		{
			INACTIVE_MODULE_ERROR();
			static D3D11_BUFFER_DESC result;
			return result;
		}

		ID3D11Buffer* IndexBufferObject::getBufferInterface() const
		{
			INACTIVE_MODULE_ERROR();
			return nullptr;
		}

		D3D11_MAPPED_SUBRESOURCE* IndexBufferObject::getBindResource() const
		{
			INACTIVE_MODULE_ERROR();
			return nullptr;
		}
		
		bool IndexBufferObject::isBind() const
		{
			INACTIVE_MODULE_ERROR();
			return false;
		}

		void IndexBufferObject::setBindResource(const D3D11_MAPPED_SUBRESOURCE& mapData)
		{
			INACTIVE_MODULE_ERROR();
		}
	}
}