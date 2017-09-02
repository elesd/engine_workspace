#include <stdafx.h>
#include <engine/video/winapi/BufferObjectFactoryImpl.h>
///////////////////////////////////////////////////////////////////////////////

#if ENGINE_USE_WINAPI

#include <engine/video/winapi/BufferContextImpl.h>
#include <engine/video/winapi/IndexBufferObject.h>
#include <engine/video/winapi/VertexBufferObject.h>

namespace engine
{
	namespace winapi
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

		std::unique_ptr<BufferContext> BufferObjectFactoryImpl::createBufferContextImpl() const
		{
			return std::make_unique<BufferContextImpl>(getRenderContext(), _members->driver);
		}

		std::unique_ptr<BufferObject> BufferObjectFactoryImpl::createVertexBufferObjectImpl(size_t size) const
		{
			return std::make_unique<VertexBufferObject>(size, _members->driver);
		}
		
		std::unique_ptr<BufferObject> BufferObjectFactoryImpl::createIndexBufferObjectImpl(size_t size) const
		{
			return std::make_unique<IndexBufferObject>(size, _members->driver);
		}
	}
}


#endif