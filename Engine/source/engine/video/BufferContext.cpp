#include <stdafx.h>
#include <engine/video/BufferContext.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/AttributeFormat.h>

namespace engine
{

	struct BufferContextPrivate
	{
		std::unique_ptr<IndexBufferBase> indexBuffer;
		std::unique_ptr<VertexBuffer> vertexBuffer;
		RenderContext* renderContext = nullptr;
		Driver* driver = nullptr;
		bool buffersBind = false;
		bool bind = false;
		bool finalized = false;
		BufferContextPrivate(RenderContext* renderContext, Driver* driver)
			: renderContext(renderContext)
			, driver(driver)
		{
		}
	};

	BufferContext::BufferContext(RenderContext* renderContext, Driver* driver)
		: _members(new BufferContextPrivate(renderContext, driver))
	{

	}

	BufferContext::~BufferContext()
	{
		if(allBuffersBound())
		{
			unbindBuffers();
		}

		delete _members;
		_members = nullptr;
	}

	void BufferContext::finalize()
	{
		ASSERT(_members->finalized == false);
		finalizeImpl();
		_members->finalized = true;
	}


	bool BufferContext::hasIndexBuffer() const
	{
		return _members->indexBuffer.get() != nullptr;
	}

	bool BufferContext::hasVertexBuffer() const
	{
		return _members->vertexBuffer.get() != nullptr;
	}

	void BufferContext::bindBuffers()
	{
		ASSERT(_members->finalized);
		bindBuffersImpl();
	}

	void BufferContext::unbindBuffers()
	{
		ASSERT(_members->finalized);
		unbindBuffersImpl();
	}

	bool BufferContext::allBuffersBound() const
	{
		ASSERT(_members->finalized);

		bool allBound = true;
		if(getVertexBuffer())
		{
			allBound = allBound && getVertexBuffer()->getBufferObject()->isBound();
		}
		if(getIndexBuffer())
		{
			allBound = allBound && getIndexBuffer()->getBufferObject()->isBound();
		}
		return allBound;
	}

	VertexBuffer* BufferContext::initVertexBuffer(const AttributeFormat& attributeFormat)
	{
		ScopeExit unbindOnExit([=]() { unbind(); });
		bind();

		std::vector<GPUMemberType> format;
		format.reserve(attributeFormat.getNumOfAttributes());
		for(uint32_t i = 0; i < attributeFormat.getNumOfAttributes(); ++i)
		{
			format.push_back(attributeFormat.getAttribute(i).type);
		}
		_members->vertexBuffer.reset(new engine::VertexBuffer(format));
		return _members->vertexBuffer.get();
	}


	void BufferContext::setIndexBuffer(std::unique_ptr<IndexBufferBase>&& buffer)
	{
		_members->indexBuffer = std::move(buffer);
	}
	
	RenderContext* BufferContext::getRenderContext()
	{
		return _members->renderContext;
	}

	Driver* BufferContext::getDriver() const
	{
		return _members->driver;
	}

	const IndexBufferBase* BufferContext::getIndexBuffer() const
	{
		return _members->indexBuffer.get();
	}

	const VertexBuffer* BufferContext::getVertexBuffer() const
	{
		return _members->vertexBuffer.get();
	}

	IndexBufferBase* BufferContext::accessIndexBuffer()
	{
		return _members->indexBuffer.get();
	}

	VertexBuffer* BufferContext::accessVertexBuffer()
	{
		return _members->vertexBuffer.get();
	}
}