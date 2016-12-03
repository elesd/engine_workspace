#include "stdafx.h"
#if ENGINE_USE_WINAPI == 0

#include "engine/app/winapi/WinApiApplicationParameter.h"

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
			HARD_ASSERT("Not implemented module");
		}

		WinApiApplicationParameter::~WinApiApplicationParameter()
		{
			HARD_ASSERT("Not implemented module");
		}

		HINSTANCE WinApiApplicationParameter::getInstance() const
		{
			HARD_ASSERT("Not implemented module");
			return nullptr;
		}

		int WinApiApplicationParameter::getCmdShow() const
		{
			HARD_ASSERT("Not implemented module");
			return 0;
		}
	}
}
#endif