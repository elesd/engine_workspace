#include <stdafx.h>
#include <engine/video/BufferObjectFactory.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/BufferObject.h>

namespace engine
{
	std::unique_ptr<BufferObject> BufferObjectFactory::createVertexBufferObject(BufferObjectTypes type, size_t size) const
	{
		switch(type)
		{
			case BufferObjectTypes::VertexBufferObject: return createVertexBufferObject(size);
			case BufferObjectTypes::VertexBufferArray: return createVertexBufferArray(size);
			default: ASSERT("Unknown vertex buffer object type"); return nullptr;
		}
	}

}