#pragma once

namespace engine
{
	class IndexBuffer 
	{
	public:
		IndexBuffer();
		IndexBuffer(const std::vector<char>& data);
		~IndexBuffer();
	};
}