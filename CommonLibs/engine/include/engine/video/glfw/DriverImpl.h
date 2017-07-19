#pragma once

#include <engine/video/glew/DriverImpl.h>

namespace engine
{
	namespace glfw
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
			void initDeviceImpl(const DeviceParameters& params) override;
			/**Initialize based on the given window*/
			void initImpl(const DriverInitParameters& params) override;
			void swapBufferImpl() override;
		};
	}
}