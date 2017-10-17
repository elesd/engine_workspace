#pragma once

#include <engine/constraints/NonMoveable.h>
#include <engine/constraints/NonCopyable.h>

#include <engine/video/IndexBuffer.h>
#include <engine/video/IndexBufferBase.h>
#include <engine/video/VertexBuffer.h>

#include <engine/utils/ScopeExit.h>

namespace engine
{
	class AttributeFormat;
	class RenderContext;
	class VertexBuffer;

	class Geometry
		: private NonCopyable
		, private NonMoveable
	{
	public:
		Geometry(RenderContext* renderContext, Driver* driver);
		virtual ~Geometry();
		void finalize();
		bool hasIndexBuffer() const;
		bool hasVertexBuffer() const;

		void bindBuffers();
		void unbindBuffers();
		bool allBuffersBound() const;

		template<typename T>
		void setupIndexBuffer(PrimitiveType type, const std::vector<T>& data);

		template<typename T>
		void setupVertexBuffer(const AttributeFormat& attributeFormat, const std::vector<T>& data);
		const IndexBufferBase* getIndexBuffer() const;
		const VertexBuffer* getVertexBuffer() const;
	protected:
		IndexBufferBase* accessIndexBuffer();
		VertexBuffer* accessVertexBuffer();
		RenderContext* getRenderContext();
		Driver* getDriver() const;
	private:
		template<typename T>
		IndexBufferBase* initIndexBuffer(PrimitiveType type, const std::vector<T>& data);

		VertexBuffer* initVertexBuffer(const AttributeFormat& attributeFormat);

		void setIndexBuffer(std::unique_ptr<IndexBufferBase>&& buffer);
		virtual bool isBound() const = 0;
		virtual void bindBuffersImpl() = 0;
		virtual void unbindBuffersImpl() = 0;
		virtual void setupLayout() = 0;
		virtual void bind() = 0;
		virtual void unbind() = 0;
		virtual void finalizeImpl() = 0;

	private:
		struct BufferContextPrivate* _members = nullptr;
	};


	template<typename T>
	void Geometry::setupIndexBuffer(PrimitiveType type, const std::vector<T>& data)
	{
		ASSERT(hasIndexBuffer() == false);
		initIndexBuffer(type, data);
	}

	template<typename T>
	void Geometry::setupVertexBuffer(const AttributeFormat& attributeFormat, const std::vector<T>& data)
	{
		ASSERT(hasVertexBuffer() == false);
		VertexBuffer* buffer = initVertexBuffer(attributeFormat);
		buffer->fill(data);
		setupLayout();
	}

	template<typename T>
	IndexBufferBase* Geometry::initIndexBuffer(PrimitiveType type, const std::vector<T>& data)
	{
		ScopeExit unbindOnExit([=]() { unbind(); });
		bind();

		IndexBufferBase* result = nullptr;


		std::unique_ptr<engine::IndexBufferBase> buffer(new typename engine::IndexBuffer<T>(type, data));
		result = buffer.get();
		setIndexBuffer(std::move(buffer));

		return result;
	}

}