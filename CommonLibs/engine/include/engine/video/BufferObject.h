#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	enum class BufferMappingType
	{
		BufferObject,
		BufferArrayObject
	};

	class Driver;
	class BufferObject
		: private NonCopyable
		, private NonMoveable
	{
	protected:
		BufferObject() = default;

	public:
		virtual ~BufferObject() {};


		virtual void bind() = 0;
		virtual void unbind() = 0;
		virtual bool isBound() const = 0;
		virtual void setData(const char* data, size_t size) = 0;
	};
}