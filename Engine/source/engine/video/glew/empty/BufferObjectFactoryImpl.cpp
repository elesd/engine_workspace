#include <stdafx.h>
#include <engine/video/glew/BufferObjectFactoryImpl.h>
///////////////////////////////////////////////////////////////////////////////

#if !ENGINE_USE_GLEW

#include <engine/video/BufferContext.h>
#include <engine/video/BufferObject.h>
namespace engine
{
	namespace glew
	{
		BufferObjectFactoryImpl::BufferObjectFactoryImpl(Driver* driver)
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
			return nullptr;
		}

		std::unique_ptr<BufferObject> BufferObjectFactoryImpl::createIndexBufferObjectImpl(size_t size) const
		{
			INACTIVE_MODULE_ERROR();
			return nullptr;
		}

		std::unique_ptr<BufferContext> BufferObjectFactoryImpl::createBufferContextImpl() const
		{
			INACTIVE_MODULE_ERROR();
			return nullptr;
		}
	}
}

#endif