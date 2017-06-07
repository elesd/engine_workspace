#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	enum class GPUMemberType;

	class VertexBuffer 
	{
	public:
		VertexBuffer();
		explicit VertexBuffer(const std::vector<GPUMemberType>& format, const std::vector<char>& data = {});
		VertexBuffer(const VertexBuffer&);
		VertexBuffer(VertexBuffer&&);
		~VertexBuffer();

		VertexBuffer& operator=(const VertexBuffer&);
		VertexBuffer& operator=(VertexBuffer&&);
		void setFormat(const std::vector<GPUMemberType>& format);
		void fill(const std::vector<char>& data);
		size_t getVertexCount() const;
	private:
		struct VertexBufferPrivate* _members = nullptr;
	};
}