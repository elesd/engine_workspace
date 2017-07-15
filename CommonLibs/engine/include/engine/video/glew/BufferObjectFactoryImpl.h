#pragma once

#include <engine/video/BufferObjectFactory.h>

namespace engine
{
	class Driver;
	class RenderContext;
	

	namespace glew
	{
		class BufferObjectFactoryImpl
			: public BufferObjectFactory
		{
		public:
			explicit BufferObjectFactoryImpl(Driver* driver);
			~BufferObjectFactoryImpl() override;

		private:
			std::unique_ptr<BufferObject> createVertexBufferObjectImpl(size_t size) const override;
			std::unique_ptr<BufferObject> createIndexBufferObjectImpl(size_t size) const override;
			std::unique_ptr<BufferContext> createBufferContextImpl() const override;


		private:
			struct BufferObjectFactoryImplPrivate* _members = nullptr;
		};
	}
}