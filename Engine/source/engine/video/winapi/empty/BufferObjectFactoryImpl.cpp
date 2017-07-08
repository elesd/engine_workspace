#include <stdafx.h>
#include <engine/video/winapi/BufferObjectFactoryImpl.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/winapi/IndexBufferObject.h>
#include <engine/video/winapi/VertexBufferObject.h>

namespace engine
{
	namespace winapi
	{
		struct BufferObjectFactoryImplPrivate
		{
			
		};

		BufferObjectFactoryImpl::BufferObjectFactoryImpl(Driver* driver)
			: _members()
		{
			INACTIVE_MODULE_ERROR();
		}
		
		BufferObjectFactoryImpl::~BufferObjectFactoryImpl() 
		{
			INACTIVE_MODULE_ERROR();
		}

		std::unique_ptr<BufferObject> BufferObjectFactoryImpl::createVertexBufferObjectImpl(size_t size) const
		{
			INACTIVE_MODULE_ERROR();
			return std::unique_ptr<BufferObject>();
		}


		std::unique_ptr<BufferObject> BufferObjectFactoryImpl::createIndexBufferObjectImpl(size_t size) const
		{
			INACTIVE_MODULE_ERROR();
			return std::unique_ptr<IndexBufferObject>();
		}
	}
}