#pragma once

#include <engine/video/BufferObjectFactory.h>

namespace engine
{
	class Driver;
	namespace winapi
	{

		class BufferObjectFactoryImpl
			: public BufferObjectFactory
		{
			friend class WindowManagerImpl;
		private:
			explicit BufferObjectFactoryImpl(Driver* driver);
		public:
			~BufferObjectFactoryImpl() override;
		private:
			std::unique_ptr<BufferObject> createVertexBufferObjectImpl(size_t size) const override;
			std::unique_ptr<BufferObject> createIndexBufferObjectImpl(size_t size) const override;

		private:
			struct BufferObjectFactoryImplPrivate* _members = nullptr;
		};
	}
}