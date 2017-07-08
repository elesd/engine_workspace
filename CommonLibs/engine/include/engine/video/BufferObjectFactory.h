#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	class BufferObject;

	class BufferObjectFactory
		: private NonCopyable
		, private NonMoveable
	{
	protected:
		BufferObjectFactory() = default;
	public:
		virtual ~BufferObjectFactory() {}
		std::unique_ptr<BufferObject> createVertexBufferObject(size_t size) const;
		std::unique_ptr<BufferObject> createIndexBufferObject(size_t size) const;

	private:
		virtual std::unique_ptr<BufferObject> createVertexBufferObjectImpl(size_t size) const = 0;
		virtual std::unique_ptr<BufferObject> createIndexBufferObjectImpl(size_t size) const = 0;
	};
}