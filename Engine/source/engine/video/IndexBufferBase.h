#pragma once

#include <engine/constraints/NonCopyable.h>

namespace engine
{
	class RenderContext;
	class BufferObject;
	enum class PrimitiveType;

	class IndexBufferBase
		: private NonCopyable
	{
	protected:
		IndexBufferBase(PrimitiveType primitiveType);
	public:
		IndexBufferBase(IndexBufferBase&&);
		virtual IndexBufferBase& operator=(IndexBufferBase&&);
		virtual ~IndexBufferBase();

		virtual size_t count() const = 0;
		virtual size_t getSize() const = 0;
		virtual size_t getStride() const = 0;

		virtual void map(RenderContext* renderContext) = 0;
		virtual bool isMapped() const = 0;
		virtual void unmap() = 0;
		BufferObject* getBufferObject() const;

		PrimitiveType getPrimitiveType() const;
	protected:
		void setBufferObject(RenderContext* renderContext, std::unique_ptr<BufferObject>&& bufferObject);
		void releaseBufferObject();
	private:
		struct IndexBufferBasePrivate* _members = nullptr;
	};
}