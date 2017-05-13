#include <stdafx.h>
#if ENGINE_USE_WINAPI == 0

#include <engine/app/winapi/WinApiApplicationParameter.h>

/////////////////////////////////////////////////

namespace engine
{
	namespace winapi
	{

		WinApiApplicationParameter::WinApiApplicationParameter(HINSTANCE ,
															   HINSTANCE ,
															   LPSTR ,
															   int )
		{
			HARD_FAIL("Inactive module");
		}

		WinApiApplicationParameter::~WinApiApplicationParameter()
		{
			HARD_FAIL("Inactive module");
		}

		HINSTANCE WinApiApplicationParameter::getInstance() const
		{
			HARD_FAIL("Inactive module");
			return nullptr;
		}

		int WinApiApplicationParameter::getCmdShow() const
		{
			HARD_ASSERT("Inactive module");
			return 0;
		}
	}
}
#endif