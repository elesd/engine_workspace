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
		std::vector<GPUMemberType> format;
		VertexBufferMappingData mappingData;

		VertexBufferPrivate() = default;
		VertexBufferPrivate(const std::vector<GPUMemberType>& format, const std::vector<char>& data = {})
			: format(format)
			, data(data)
		{}
	};
	
	VertexBuffer::VertexBuffer(const std::vector<GPUMemberType>& format, const std::vector<char>& data)
		: _members(new VertexBufferPrivate(format, data))
	{

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

	void VertexBuffer::setFormat(const std::vector<GPUMemberType>& format)
	{
		_members->format = format;
	}

	void VertexBuffer::fill(const std::vector<char>& data)
	{
		_members->data = data;
	}

	size_t VertexBuffer::getVertexCount() const
	{
		size_t vertexSize = 0;
		for(GPUMemberType type : _members->format)
		{
			vertexSize += GPUMemberTypeTraits::getSize(type);
		}
		return _members->data.size() / vertexSize;
	}

	size_t VertexBuffer::getSize() const
	{
		return _members->data.size();
	}
	
	void VertexBuffer::map(RenderContext* renderContext)
	{
		ASSERT(isMapped() == false);
		_members->mappingData.renderContext = renderContext;
		_members->mappingData.bufferObject = renderContext->createVertexBufferObject(getSize());
		_members->mappingData.bufferObject->bind();
		_members->mappingData.bufferObject->setData(_members->data);
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

	VertexBuffer VertexBuffer::cloneClientData() const
	{
		VertexBuffer result(_members->format, _members->data);
		return result;
	}



}