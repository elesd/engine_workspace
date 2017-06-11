#include <stdafx.h>
#include <engine/video/IndexBufferBase.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/BufferObject.h>

namespace engine
{
	struct IndexBufferMapData
	{
		std::unique_ptr<BufferObject> bufferObject;
		RenderContext* renderContext = nullptr;
	};
	struct IndexBufferBasePrivate
	{
		IndexBufferMapData mappingData;
		PrimitiveType primitiveType;
		IndexBufferBasePrivate(PrimitiveType primitiveType)
			: primitiveType(primitiveType)
		{ }
	};


	IndexBufferBase::IndexBufferBase(PrimitiveType primitiveType)
		:_members(new IndexBufferBasePrivate(primitiveType))
	{

	}

	IndexBufferBase::IndexBufferBase(IndexBufferBase&& o)
		:_members(o._members)
	{
		o._members = nullptr;
	}

	IndexBufferBase& IndexBufferBase::operator=(IndexBufferBase&& o)
	{
		delete _members;
		_members = o._members;
		o._members = nullptr;
		return *this;
	}

	IndexBufferBase::~IndexBufferBase()
	{
		delete _members;
		_members = nullptr;
	}

	BufferObject* IndexBufferBase::getBufferObject() const
	{
		return _members->mappingData.bufferObject.get();
	}


	PrimitiveType IndexBufferBase::getPrimitiveType() const
	{
		return _members->primitiveType;
	}

	void IndexBufferBase::setBufferObject(RenderContext* renderContext, std::unique_ptr<BufferObject>&& bufferObject)
	{
		_members->mappingData.renderContext = renderContext;
		_members->mappingData.bufferObject = std::move(bufferObject);
	}

	void IndexBufferBase::releaseBufferObject()
	{
		_members->mappingData.renderContext = nullptr;
		_members->mappingData.bufferObject.reset();
	}
}