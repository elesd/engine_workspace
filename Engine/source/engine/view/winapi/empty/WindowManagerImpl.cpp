#include "stdafx.h"
#if ENGINE_USE_WINAPI == 0

#include "engine/view/winapi/WindowManagerImpl.h"
///////////////////////////////////////////////////

#include "engine/video/Driver.h"

namespace engine
{
	namespace view
	{
		namespace winapi
		{

			WindowManagerImpl::WindowManagerImpl()
			{
				HARD_FAIL("Not implemented module");
			}

			WindowManagerImpl::~WindowManagerImpl()
			{
				HARD_FAIL("Not implemented module");
			}

			view::Window *WindowManagerImpl::createMainWindowImpl(const view::WindowParameter &, const std::string &)
			{
				HARD_FAIL("Not implemented module");
				return nullptr;
			}

			view::Window *WindowManagerImpl::createFullScreenMainWindowImpl(const uint32_t , const uint32_t , const std::string &, uint32_t)
			{
				HARD_FAIL("Not implemented module");
				return nullptr;
			}

			view::Window *WindowManagerImpl::createSecondaryWindowImpl(const view::WindowParameter &,
																	   const std::string &,
																	   view::Window *)
			{
				HARD_FAIL("Not implemented module");
				return nullptr;
			}

			view::Window *WindowManagerImpl::createSecondaryFullScreenWindowImpl(const uint32_t, const uint32_t, const std::string &, uint32_t, view::Window *)
			{
				HARD_FAIL("Not implemented module");
				return nullptr;
			}

			uint32_t WindowManagerImpl::getMonitorCount() const
			{
				HARD_FAIL("Not implemented module");
			}

			uint32_t WindowManagerImpl::getMainMonitorId() const
			{
				HARD_FAIL("Not implemented module");
				return 0;
			}

			void WindowManagerImpl::RegisterWindowClass()
			{
				HARD_FAIL("Not implemented module");
			}

			std::unique_ptr<video::Driver> WindowManagerImpl::createDriverForWindow(const video::DriverInitParameters &, Window *) const
			{
				HARD_FAIL("Not implemented module");
				return nullptr;
			}
		}
	}
}
#endif