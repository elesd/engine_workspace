#pragma once

#include <engine/constraints/NonCopyable.h>

#include <engine/video/BufferObject.h>
#include <engine/video/IndexBufferBase.h>

#include <memory>

namespace engine
{
	class RenderContext;

	
	template<typename SIZE_TYPE>
	class  IndexBuffer
		: public IndexBufferBase
	{
	public:
		IndexBuffer(PrimitiveType type, std::vector<SIZE_TYPE> data);
		IndexBuffer(IndexBuffer&&);
		~IndexBuffer() override;
		IndexBuffer& operator=(IndexBuffer&&);

		size_t count() const override;
		size_t getSize() const override;
		size_t getStride() const override;

		void map(RenderContext* renderContext) override;
		bool isMapped() const override;
		void unmap() override;

		IndexBuffer cloneClientData() const;
	private:
		const char* getDataPtr() const;
	private:
		std::vector<SIZE_TYPE> _data;
	};
}

#include <engine/video/IndexBuffer.hpp>