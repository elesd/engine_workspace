#include <stdafx.h>
#include <engine/video/IndexBuffer.h>

namespace engine
{
	IndexBuffer::IndexBuffer()
		: VideoBufferBase()
	{

	}

	IndexBuffer::IndexBuffer(const std::vector<char>& data)
		: VideoBufferBase(data)
	{

	}

	IndexBuffer::~IndexBuffer()
	{

	}
}