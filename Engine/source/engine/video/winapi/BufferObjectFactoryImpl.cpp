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

		std::unique_ptr<BufferObject> BufferObjectFactoryImpl::createVertexBufferObject(size_t size) const
		{
			return std::make_unique<VertexBufferObject>(size, _members->driver);
		}

		std::unique_ptr<BufferObject> BufferObjectFactoryImpl::createVertexBufferArray(size_t size) const
		{
			UNSUPPORTED_ERROR();
			return std::unique_ptr<BufferObject>();
		}
		
		std::unique_ptr<BufferObject> BufferObjectFactoryImpl::createIndexBufferObjectImpl(size_t size) const
		{
			return std::make_unique<IndexBufferObject>(size, _members->driver);
		}
	}
}