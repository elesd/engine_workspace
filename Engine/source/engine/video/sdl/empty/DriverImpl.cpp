#include <stdafx.h>

#include <engine/video/sdl/DriverImpl.h>
///////////////////////////////////////////////////////////////////////////////
#if ENGINE_USE_SDL == 0

namespace engine
{
	namespace sdl
	{

		DriverImpl::DriverImpl() 
		{
			HARD_FAIL("Unimplemented module");
		}
		DriverImpl::~DriverImpl()
		{
			HARD_FAIL("Unimplemented module");
		}

		void DriverImpl::initImpl(const DriverInitParameters& params)
		{
			HARD_FAIL("Unimplemented module");
		}
	}
}
#endif