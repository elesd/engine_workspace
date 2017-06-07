#include <stdafx.h>
#include <engine/video/VertexBuffer.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/GPUTypes.h>

namespace engine
{
	struct VertexBufferPrivate
	{
		std::vector<char> data;
		std::vector<GPUMemberType> format;
		VertexBufferPrivate() = default;
		VertexBufferPrivate(const std::vector<GPUMemberType>& format, const std::vector<char>& data = {})
			: format(format)
			, data(data)
		{}
	};
	VertexBuffer::VertexBuffer()
		: _members(new VertexBufferPrivate())
	{

	}

	VertexBuffer::VertexBuffer(const std::vector<GPUMemberType>& format, const std::vector<char>& data)
		: _members(new VertexBufferPrivate(format, data))
	{

	}

	VertexBuffer::VertexBuffer(const VertexBuffer& o)
		: _members(o._members ? new VertexBufferPrivate(*o._members), nullptr)
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

	VertexBuffer& VertexBuffer::operator=(const VertexBuffer& o)
	{
		delete _members;
		_members = o._members ? new VertexBufferPrivate(*o._members) : nullptr;
		return *this;
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
}