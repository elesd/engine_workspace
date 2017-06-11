#pragma once

#include <engine/constraints/NonCopyable.h>

namespace engine
{
	class BufferObject;
	class RenderContext;

	enum class GPUMemberType;

	class VertexBuffer 
		: private NonCopyable
	{
	public:
		VertexBuffer(const std::vector<GPUMemberType>& format, const std::vector<char>& data = {});
		VertexBuffer(VertexBuffer&&);
		~VertexBuffer();

		VertexBuffer& operator=(VertexBuffer&&);
		void setFormat(const std::vector<GPUMemberType>& format);
		void fill(const std::vector<char>& data);
		size_t getVertexCount() const;
		size_t getStride() const;
		size_t getSize() const;
		
		void map(RenderContext* renderContext);
		bool isMapped() const;
		void unmap();

		BufferObject* getBufferObject() const;
		VertexBuffer cloneClientData() const;
	private:
		void recalcStride();
	private:

		struct VertexBufferPrivate* _members = nullptr;
	};
}