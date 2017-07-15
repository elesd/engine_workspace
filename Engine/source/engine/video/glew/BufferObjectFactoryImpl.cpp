#include <stdafx.h>
#include <engine/video/glew/BufferObjectFactoryImpl.h>
///////////////////////////////////////////////////////////////////////////////

#if ENGINE_USE_GLEW 


#include <engine/video/glew/BufferContextImpl.h>
#include <engine/video/glew/VertexBufferObject.h>
#include <engine/video/glew/IndexBufferObject.h>

namespace engine
{
	namespace glew
	{
		struct BufferObjectFactoryImplPrivate
		{
			Driver* driver = nullptr;
			BufferObjectFactoryImplPrivate(Driver* driver)
				: driver(driver)
			{ }
		};

		BufferObjectFactoryImpl::BufferObjectFactoryImpl(Driver* driver)
			: _members(new BufferObjectFactoryImplPrivate(driver))
		{

		}

		BufferObjectFactoryImpl::~BufferObjectFactoryImpl()
		{
			delete _members;
			_members = nullptr;
		}


		std::unique_ptr<BufferObject> BufferObjectFactoryImpl::createVertexBufferObjectImpl(size_t size) const
		{
			return std::make_unique<VertexBufferObject>(size, _members->driver);
		}

		std::unique_ptr<BufferObject> BufferObjectFactoryImpl::createIndexBufferObjectImpl(size_t size) const
		{
			return std::make_unique<IndexBufferObject>(size, _members->driver);
		}

		std::unique_ptr<BufferContext> BufferObjectFactoryImpl::createBufferContextImpl() const
		{
			return std::make_unique<BufferContextImpl>(getRenderContext(), _members->driver);
		}
	}
}

#else

#include <engine/video/glew/empty/BufferObjectFactoryImpl.cpp>

#endif