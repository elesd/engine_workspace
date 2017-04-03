#include <stdafx.h>
#include <engine/app/winapi/ApplicationImpl.h>
///////////////////////////////////////////////////////////////////////////////
#include <engine/app/IMain.h>

#include <engine/app/winapi/WinApiApplicationParameter.h>
#include <engine/view/winapi/WindowImpl.h>


#if ENGINE_USE_WINAPI

namespace engine
{
	namespace winapi
	{
		ApplicationImpl::ApplicationImpl(std::unique_ptr<IApplicationParameter> arguments, std::unique_ptr<IMain> main)
			:Application(std::move(arguments), std::move(main))
		{
		}

		void ApplicationImpl::updateImpl()
		{
			MSG msg;
			memset(&msg, 0, sizeof(MSG));
			while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				// translate keystroke messages into the right format
				TranslateMessage(&msg);

				// send the message to the WindowProc function
				DispatchMessage(&msg);
				if(msg.message == WM_QUIT)
					stop();
				memset(&msg, 0, sizeof(MSG));
			}
		}

		bool ApplicationImpl::handleEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			bool handled = false;
			switch(message)
			{
				case WM_DESTROY:
				{
					PostQuitMessage(0);
					handled = true;
				} break;
			}
			return handled;
		}
	}
}

#endif