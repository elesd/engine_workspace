#include <stdafx.h>

#include <engine/video/winapi/DriverImpl.h>
///////////////////////////////////////////////////////////////////////////////
#if ENGINE_USE_WINAPI == 0

namespace engine
{
	namespace winapi
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