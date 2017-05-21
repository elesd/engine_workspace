#pragma once

#include <engine/video/VideoBufferBase.h>

namespace engine
{
	class IndexBuffer : public VideoBufferBase
	{
	public:
		IndexBuffer();
		IndexBuffer(const std::vector<char>& data);
		~IndexBuffer() override;
	};
}