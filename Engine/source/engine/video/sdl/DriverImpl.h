#pragma once

#include <engine/video/glew/DriverImpl.h>

namespace engine
{
	namespace sdl
	{
		/**
		* Video driver implementation for winapi
		*/
		class DriverImpl : public glew::DriverImpl
		{
		public:
			/**Simple constructor*/
			DriverImpl();
			/**For PIMPL*/
			~DriverImpl() override;

		private:
			void initContextImpl(const DriverContextParameters& params);
			/**Initialize based on the given window*/
			void initImpl(const DriverInitParameters& params, Window *window) override;
			void swapBufferImpl() override;

		private:
			struct DriverImplPrivate* _members = nullptr;
		};
	}
}