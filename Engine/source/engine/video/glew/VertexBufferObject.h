#pragma once

#include <engine/video/BufferObject.h>
namespace engine
{
	namespace glew
	{
		class VertexBufferObject
			: public BufferObject
		{
		public:
			VertexBufferObject(size_t size, Driver* driver);
			~VertexBufferObject() override;

			void bind() override;
			void unbind() override;
			void setData(const char* data, size_t size) override;

			bool isBind() const;
		private:
			struct VertexBufferObjectPrivate* _members = nullptr;
		};
	}
}