#include <stdafx.h>
#include <engine/video/Geometry.h>
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

	Geometry::Geometry(RenderContext* renderContext, Driver* driver)
		: _members(new BufferContextPrivate(renderContext, driver))
	{

	}

	Geometry::~Geometry()
	{
		if(allBuffersBound())
		{
			unbindBuffers();
		}

		delete _members;
		_members = nullptr;
	}

	void Geometry::finalize()
	{
		ASSERT(_members->finalized == false);
		finalizeImpl();
		_members->finalized = true;
	}


	bool Geometry::hasIndexBuffer() const
	{
		return _members->indexBuffer.get() != nullptr;
	}

	bool Geometry::hasVertexBuffer() const
	{
		return _members->vertexBuffer.get() != nullptr;
	}

	void Geometry::bindBuffers()
	{
		ASSERT(_members->finalized);
		bindBuffersImpl();
	}

	void Geometry::unbindBuffers()
	{
		ASSERT(_members->finalized);
		unbindBuffersImpl();
	}

	bool Geometry::allBuffersBound() const
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

	VertexBuffer* Geometry::initVertexBuffer(const AttributeFormat& attributeFormat)
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


	void Geometry::setIndexBuffer(std::unique_ptr<IndexBufferBase>&& buffer)
	{
		_members->indexBuffer = std::move(buffer);
	}
	
	RenderContext* Geometry::getRenderContext()
	{
		return _members->renderContext;
	}

	Driver* Geometry::getDriver() const
	{
		return _members->driver;
	}

	const IndexBufferBase* Geometry::getIndexBuffer() const
	{
		return _members->indexBuffer.get();
	}

	const VertexBuffer* Geometry::getVertexBuffer() const
	{
		return _members->vertexBuffer.get();
	}

	IndexBufferBase* Geometry::accessIndexBuffer()
	{
		return _members->indexBuffer.get();
	}

	VertexBuffer* Geometry::accessVertexBuffer()
	{
		return _members->vertexBuffer.get();
	}
}