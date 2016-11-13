#include "stdafx.h"
#if ENGINE_USE_WINAPI == 0

#include "engine/modules/winapi/WindowManagerImpl.h"
///////////////////////////////////////////////////


namespace engine
{
	namespace winapi
	{

		WindowManagerImpl::WindowManagerImpl()
		{
			HARD_ASSERT("Not implemented module");
		}

		WindowManagerImpl::~WindowManagerImpl()
		{
			HARD_ASSERT("Not implemented module");
		}

		view::Window *WindowManagerImpl::createMainWindowImpl(const view::WindowParameter &, const std::string &)
		{
			HARD_ASSERT("Not implemented module");
			return nullptr;
		}

		view::Window *WindowManagerImpl::createFullScreenMainWindowImpl(const uint32_t , const uint32_t , const std::string &, uint32_t)
		{
			HARD_ASSERT("Not implemented module");
			return nullptr;
		}

		view::Window *WindowManagerImpl::createSecondaryWindowImpl(const view::WindowParameter &,
			const std::string &,
			view::Window *)
		{
			HARD_ASSERT("Not implemented module");
			return nullptr;
		}

		view::Window *WindowManagerImpl::createSecondaryFullScreenWindowImpl(const uint32_t, const uint32_t, const std::string &, uint32_t, view::Window *)
		{
			HARD_ASSERT("Not implemented module");
			return nullptr;
		}

		uint32_t WindowManagerImpl::getMonitorCount() const
		{
			HARD_ASSERT("Not implemented module");
		}

		uint32_t WindowManagerImpl::getMainMonitorId() const
		{
			HARD_ASSERT("Not implemented module");
			return 0;
		}

		void WindowManagerImpl::RegisterWindowClass()
		{
			HARD_ASSERT("Not implemented module");
		}
	}
}
#endif