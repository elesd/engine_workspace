#include <stdafx.h>
#include <engine/video/BufferObjectFactory.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/BufferObject.h>
#include <engine/video/Geometry.h>

namespace engine
{
	struct BufferObjectFactoryPrivate
	{
		RenderContext* renderContext = nullptr;
	};

	BufferObjectFactory::BufferObjectFactory()
		:_members(new BufferObjectFactoryPrivate())
	{

	}

	BufferObjectFactory::~BufferObjectFactory()
	{
		delete _members;
		_members = nullptr;
	}

	void BufferObjectFactory::setup(RenderContext* renderContext)
	{
		_members->renderContext = renderContext;
	}


	bool BufferObjectFactory::isReady() const
	{
		return _members->renderContext != nullptr;
	}

	RenderContext* BufferObjectFactory::getRenderContext() const
	{
		return _members->renderContext;
	}

	std::unique_ptr<Geometry> BufferObjectFactory::createBufferContext() const
	{
		ASSERT(isReady());
		return createBufferContextImpl();
	}

	std::unique_ptr<BufferObject> BufferObjectFactory::createVertexBufferObject(size_t size) const
	{
		ASSERT(isReady());
		return createVertexBufferObjectImpl(size);
	}

	std::unique_ptr<BufferObject> BufferObjectFactory::createIndexBufferObject(size_t size) const
	{
		ASSERT(isReady());
		return createIndexBufferObjectImpl(size);
	}
}