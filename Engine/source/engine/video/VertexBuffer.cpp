#include <stdafx.h>
#include <engine/video/VertexBuffer.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/render/RenderContext.h>

#include <engine/video/BufferObject.h>
#include <engine/video/BufferObjectFactory.h>
#include <engine/video/GPUTypes.h>

namespace engine
{
	struct VertexBufferMappingData
	{
		RenderContext* renderContext;
		std::unique_ptr<BufferObject> bufferObject;
	};


	struct VertexBufferPrivate
	{
		std::vector<char> data;
		std::vector<GPUMemberType> attributeTypes;
		size_t stride = 0;
		VertexBufferMappingData mappingData;

		VertexBufferPrivate() = default;
		VertexBufferPrivate(const std::vector<GPUMemberType>& attributeTypes, const std::vector<char>& data = {})
			: attributeTypes(attributeTypes)
			, data(data)
		{	}
	};
	
	VertexBuffer::VertexBuffer(const std::vector<GPUMemberType>& format, const std::vector<char>& data)
		: _members(new VertexBufferPrivate(format, data))
	{
		recalcStride();
	}

	VertexBuffer::VertexBuffer(VertexBuffer&& o)
		: _members(o._members)
	{
		o._members = nullptr;
	}

	VertexBuffer::~VertexBuffer()
	{
		delete _members;
		_members = nullptr;
	}

	VertexBuffer& VertexBuffer::operator=(VertexBuffer&& o)
	{
		delete _members;
		_members = o._members;
		o._members = nullptr;
		return *this;
	}

	void VertexBuffer::setFormat(const std::vector<GPUMemberType>& attributeTypes)
	{
		_members->attributeTypes = attributeTypes;
		recalcStride();
	}

	const std::vector<GPUMemberType>& VertexBuffer::getAttributeTypes() const
	{
		return _members->attributeTypes;
	}

	void VertexBuffer::fill(const std::vector<char>& data)
	{
		_members->data = data;
	}

	size_t VertexBuffer::getVertexCount() const
	{
	
		return _members->data.size() / _members->stride;
	}

	void VertexBuffer::recalcStride() 
	{
		_members->stride = 0;
		for(GPUMemberType type : _members->attributeTypes)
		{
			_members->stride += GPUMemberTypeTraits::getSize(type);
		}
	}

	size_t VertexBuffer::getSize() const
	{
		return _members->data.size();
	}

	size_t VertexBuffer::getStride() const
	{
		return _members->stride;
	}

	
	void VertexBuffer::map(RenderContext* renderContext)
	{
		ASSERT(isMapped() == false);
		_members->mappingData.renderContext = renderContext;
		_members->mappingData.bufferObject = renderContext->createVertexBufferObject(getSize());
		_members->mappingData.bufferObject->bind();
		_members->mappingData.bufferObject->setData(_members->data.data(), _members->data.size());
		_members->mappingData.bufferObject->unbind();
	}

	bool VertexBuffer::isMapped() const
	{
		return _members->mappingData.bufferObject != nullptr;
	}

	void VertexBuffer::unmap()
	{
		_members->mappingData.renderContext = nullptr;
		_members->mappingData.bufferObject.reset();
	}

	BufferObject* VertexBuffer::getBufferObject() const
	{
		ASSERT(isMapped());
		return _members->mappingData.bufferObject.get();
	}

	VertexBuffer VertexBuffer::cloneClientData() const
	{
		VertexBuffer result(_members->attributeTypes, _members->data);
		return result;
	}



}