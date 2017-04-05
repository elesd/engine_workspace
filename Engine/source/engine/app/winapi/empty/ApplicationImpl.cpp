#include <stdafx.h>
#include <engine/app/winapi/ApplicationImpl.h>
///////////////////////////////////////////////////////////////////////////////
#include <engine/app/IMain.h>

#include <engine/app/winapi/WinApiApplicationParameter.h>
#include <engine/view/winapi/WindowImpl.h>


#if !ENGINE_USE_WINAPI
namespace engine
{
	namespace winapi
	{
		ApplicationImpl::ApplicationImpl(std::unique_ptr<IApplicationParameter> arguments, std::unique_ptr<IMain> main)
			:Application(std::move(arguments), std::move(main))
		{
			HARD_FAIL("Not implemented module");
		}

		void ApplicationImpl::updateImpl()
		{
			HARD_FAIL("Not implemented module");
		}

		bool ApplicationImpl::handleEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			HARD_FAIL("Not implemented module");
			return false;
		}
	}
}

#endif