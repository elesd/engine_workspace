#pragma once

#include "engine/video/BufferDesc.h"

namespace engine
{

	namespace view
	{
		class Window;
		class WindowManager;
		struct WindowManagerPrivate;
	}

	namespace video
	{
		struct DriverInitParameters
		{
			BufferDesc description;
			int32_t sampleCount;
		};

		class Driver
		{
			friend class view::WindowManager;
			friend struct view::WindowManagerPrivate;
			
		protected:
			Driver() = default;
		public:
			virtual ~Driver() {}
			void init(const DriverInitParameters& params, view::Window *window);


		private:
			virtual void initImpl(const DriverInitParameters& params, view::Window *window) = 0;
		};
	}
}