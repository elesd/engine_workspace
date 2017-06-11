#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	class BufferObject;

	enum class BufferObjectTypes
	{
		VertexBufferObject,
		VertexBufferArray
	};
	
	class BufferObjectFactory
		: private NonCopyable
		, private NonMoveable
	{
	protected:
		BufferObjectFactory() = default;
	public:
		virtual ~BufferObjectFactory() {}
		std::unique_ptr<BufferObject> createVertexBufferObject(BufferObjectTypes type, size_t size) const;

	private:
		virtual std::unique_ptr<BufferObject> createVertexBufferObject(size_t size) const = 0;
		virtual std::unique_ptr<BufferObject> createVertexBufferArray(size_t size) const = 0;
	};
}