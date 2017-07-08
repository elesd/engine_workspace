
#include <string>
#include <engine/render/RenderContext.h>

namespace engine
{
	namespace IndexBufferPrivate
	{
		template<typename SIZE_TYPE>
		bool isSupportedSizeType();

		template<typename SIZE_TYPE>
		size_t getByteSize();

		///////////////////////////////////////////////////////////////////////

		template<typename SIZE_TYPE>
		size_t getByteSize()
		{
			static_assert(false, "Unsupported size type");
		}

		template<typename SIZE_TYPE>
		bool isSupportedSizeType() 
		{
			static_assert(false, "Unsupported size type");
			return false;
		}

		extern template	size_t getByteSize<int32_t>();
		extern template	size_t getByteSize<int16_t>();

		extern template	bool isSupportedSizeType<int32_t>();
		extern template	bool isSupportedSizeType<int16_t>();
	}

	template<typename SIZE_TYPE>
	IndexBuffer<SIZE_TYPE>::IndexBuffer(PrimitiveType type, const std::vector<SIZE_TYPE>& data)
		: IndexBufferBase(type)
		, _data(data)
	{
		IndexBufferPrivate::isSupportedSizeType<SIZE_TYPE>();
	}

	template<typename SIZE_TYPE>
	IndexBuffer<SIZE_TYPE>::IndexBuffer(IndexBuffer&& o)
		: IndexBufferBase(std::move(o))
		, _data(std::move(o._data))
	{
		IndexBufferPrivate::isSupportedSizeType<SIZE_TYPE>();
	}

	template<typename SIZE_TYPE>
	IndexBuffer<SIZE_TYPE>::~IndexBuffer()
	{

	}

	template<typename SIZE_TYPE>
	IndexBuffer<SIZE_TYPE>& IndexBuffer<SIZE_TYPE>::operator=(IndexBuffer&& o)
	{
		IndexBufferBase::operator=(std::move(o));
		_data = std::move(o._data);
	}

	template<typename SIZE_TYPE>
	size_t IndexBuffer<SIZE_TYPE>::count() const
	{
		return _data.size();
	}

	template<typename SIZE_TYPE>
	size_t IndexBuffer<SIZE_TYPE>::getSize() const
	{
		return _data.size() * getStride();
	}

	template<typename SIZE_TYPE>
	size_t IndexBuffer<SIZE_TYPE>::getStride() const
	{
		return IndexBufferPrivate::getByteSize<SIZE_TYPE>();
	}

	template<typename SIZE_TYPE>
	void IndexBuffer<SIZE_TYPE>::map(RenderContext* renderContext)
	{
		ASSERT(isMapped() == false);
		{
			std::unique_ptr<BufferObject> bufferObject = renderContext->createIndexBufferObject(getSize());
			setBufferObject(renderContext, std::move(bufferObject));
		}
		getBufferObject()->bind();
		getBufferObject()->setData(getDataPtr(), getSize());
		getBufferObject()->unbind();
	}

	template<typename SIZE_TYPE>
	bool IndexBuffer<SIZE_TYPE>::isMapped() const
	{
		return getBufferObject() != nullptr;
	}
	
	template<typename SIZE_TYPE>
	void IndexBuffer<SIZE_TYPE>::unmap()
	{
		releaseBufferObject();
	}

	template<typename SIZE_TYPE>
	IndexBuffer<SIZE_TYPE> IndexBuffer<SIZE_TYPE>::cloneClientData() const
	{
		IndexBuffer<SIZE_TYPE> result(_primitiveType, _data);
		return result;
	}

	template<typename SIZE_TYPE>
	const char* IndexBuffer<SIZE_TYPE>::getDataPtr() const
	{
		return reinterpret_cast<const char*>(_data.data());
	}
}