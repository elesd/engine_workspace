#include <stdafx.h>

#include <engine/video/Driver.h>

namespace engine
{
	void Driver::init(const DriverInitParameters &params, Window *window)
	{
		initImpl(params, window);
	}
}