#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	enum class GPUMemberType;
	class RenderContext;
	class VertexBuffer 
	{
	public:
		VertexBuffer(const std::vector<GPUMemberType>& format, const std::vector<char>& data = {});
		VertexBuffer(VertexBuffer&&);
		~VertexBuffer();

		VertexBuffer& operator=(VertexBuffer&&);
		void setFormat(const std::vector<GPUMemberType>& format);
		void fill(const std::vector<char>& data);
		size_t getVertexCount() const;
		size_t getSize() const;
		
		void map(RenderContext* renderContext);
		bool isMapped() const;
		void unmap();

		VertexBuffer cloneClientData() const;
	private:
		struct VertexBufferPrivate* _members = nullptr;
	};
}