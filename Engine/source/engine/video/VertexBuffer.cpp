#include <stdafx.h>
#include <engine/video/VertexBuffer.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/GPUTypes.h>
#include <engine/video/BufferObject.h>

namespace engine
{
	struct VertexBufferPrivate
	{
		std::unique_ptr<BufferObject> bufferObject;
		std::vector<char> data;
		std::vector<GPUMemberType> format;
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

	void VertexBuffer::setBufferObject(std::unique_ptr<BufferObject>&& bufferObject)
	{
		_members->bufferObject = std::move(bufferObject);
	}

	BufferObject* VertexBuffer::getBufferObject() const
	{
		return _members->bufferObject.get();
	}

	bool VertexBuffer::hasBufferObject() const
	{
		return getBufferObject() != nullptr;
	}

	VertexBuffer VertexBuffer::cloneClientData() const
	{
		VertexBuffer result(_members->format, _members->data);
		return result;
	}



}