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
		const std::vector<GPUMemberType>& getAttributeTypes() const;
		void fill(const std::vector<char>& data);
		template<class T>
		void fill(const std::vector<T>& data);
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
	template<class T>
	void VertexBuffer::fill(const std::vector<T>& data)
	{
		std::vector<char> rawData;
		rawData.resize(data.size() * sizeof(T));
		memcpy(rawData.data(), data.data(), rawData.size());
		fill(rawData);
	}

}