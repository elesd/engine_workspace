#include <stdafx.h>
#include <engine/video/BufferObjectFactory.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/BufferObject.h>

namespace engine
{
	std::unique_ptr<BufferObject> BufferObjectFactory::createVertexBufferObject(size_t size) const
	{
		return createVertexBufferObjectImpl(size);
	}

	std::unique_ptr<BufferObject> BufferObjectFactory::createIndexBufferObject(size_t size) const
	{
		return createIndexBufferObjectImpl(size);
	}
}