#include <stdafx.h>

#include <engine/video/glfw/DriverImpl.h>
///////////////////////////////////////////////////////////////////////////////
#if ENGINE_USE_GLFW == 0

namespace engine
{
	namespace glfw
	{

		DriverImpl::DriverImpl() 
		{
			HARD_FAIL("Unimplemented module");
		}
		DriverImpl::~DriverImpl()
		{
			HARD_FAIL("Unimplemented module");
		}

		void DriverImpl::initImpl(const DriverInitParameters& params, Window *window)
		{
			HARD_FAIL("Unimplemented module");
		}
	}
}
#endif