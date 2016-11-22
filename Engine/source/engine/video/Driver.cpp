#include "stdafx.h"

#include "engine/video/Driver.h"

namespace engine
{
	namespace video
	{
	
		void Driver::init(const DriverInitParameters &params, view::Window *window)
		{
			initImpl(params, window);
		}
	}
}