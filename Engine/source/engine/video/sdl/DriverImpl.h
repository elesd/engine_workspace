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
			/**Initialize based on the given window*/
			void initImpl(const DriverInitParameters& params, Window *window) override;
			void swapBufferImpl() override;
			void setViewPortImpl(int32_t x, int32_t y, int32_t width, int32_t height) override;

		private:
			struct DriverImplPrivate* _members = nullptr;
		};
	}
}