#pragma once

#include <engine/video/Driver.h>

namespace engine
{
	namespace winapi
	{
		/**
		* Video driver implementation for winapi
		*/
		class DriverImpl : public Driver
		{
		public:
			/**Simple constructor*/
			DriverImpl();
			/**For PIMPL*/
			~DriverImpl() override;

			/**Initialize based on the given window*/
			void initImpl(const DriverInitParameters& params, Window *window) override;
		private:
			/**PIMPL*/
			struct DriverImplPrivate *_members = nullptr;
		};
	}
}