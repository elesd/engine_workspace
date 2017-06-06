#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	enum class GPUMemberType;

	class VertexBuffer 
	{
	public:
		explicit VertexBuffer(const std::vector<GPUMemberType>& description);
		VertexBuffer(const VertexBuffer&);
		VertexBuffer(VertexBuffer&&);
		~VertexBuffer();

		VertexBuffer& operator=(const VertexBuffer&);
		VertexBuffer& operator=(VertexBuffer&&);
		void fill(const std::vector<char>& data);
	private:

	};
}