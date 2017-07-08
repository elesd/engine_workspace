#pragma once

#include <engine/video/BufferObject.h>

namespace engine
{
	class Driver;
	namespace glew
	{
		class IndexBufferObject
			: public BufferObject
		{
		public:
			IndexBufferObject(size_t size, Driver* driver);
			~IndexBufferObject() override;
			void bind() override;
			void unbind() override;
			void setData(const char* data, size_t size) override;
			bool isBind() const;
		private:
			struct IndexBufferObjectPrivate* _members = nullptr;
		};
	}
}