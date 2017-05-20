#include <stdafx.h>
#include <engine/video/VertexBuffer.h>

namespace engine
{
	VertexBuffer::VertexBuffer()
		: VideoBufferBase()
	{

	}

	VertexBuffer::VertexBuffer(const std::vector<char>& data)
		: VideoBufferBase(data)
	{

	}

	VertexBuffer::~VertexBuffer()
	{

	}
}