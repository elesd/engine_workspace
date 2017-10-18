#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	class BufferObject;
	class Geometry;
	class RenderContext;

	class BufferObjectFactory
		: private NonCopyable
		, private NonMoveable
	{
	protected:
		BufferObjectFactory();
	public:
		virtual ~BufferObjectFactory();
		std::unique_ptr<Geometry> createGeometry() const;
		std::unique_ptr<BufferObject> createVertexBufferObject(size_t size) const;
		std::unique_ptr<BufferObject> createIndexBufferObject(size_t size) const;

		void setup(RenderContext* renderContext);
		bool isReady() const;
	protected:
		RenderContext* getRenderContext() const;
	private:
		virtual std::unique_ptr<Geometry> createBufferContextImpl() const = 0;
		virtual std::unique_ptr<BufferObject> createVertexBufferObjectImpl(size_t size) const = 0;
		virtual std::unique_ptr<BufferObject> createIndexBufferObjectImpl(size_t size) const = 0;

	private:
		struct BufferObjectFactoryPrivate* _members = nullptr;
	};
}