#include "stdafx.h"
#if ENGINE_USE_WINAPI == 0

#include "engine/modules/winapi/WindowImpl.h"
/////////////////////////////////////////

namespace engine
{
	namespace winapi
	{

		WindowImpl::WindowImpl(HWND , const view::WindowParameter &, const std::string &)
			: view::Window()
		{
			HARD_ASSERT("Not implemented module");
		}

		WindowImpl::WindowImpl(HWND , const std::string &)
			: view::Window()
		{
			HARD_ASSERT("Not implemented module");
		}

		WindowImpl::~WindowImpl()
		{
			HARD_ASSERT("Not implemented module");
		}

		WindowImpl::operator bool() const
		{
			HARD_ASSERT("Not implemented module");
			return false;
		}

		void WindowImpl::setPositionImp(int32_t, int32_t)
		{
			HARD_ASSERT("Not implemented module");
		}

		void WindowImpl::setWidthImpl(uint32_t)
		{
			HARD_ASSERT("Not implemented module");
		}

		void WindowImpl::setHeightImpl(uint32_t)
		{
			HARD_ASSERT("Not implemented module");
		}

		void WindowImpl::setSizeImpl(uint32_t, uint32_t)
		{
			HARD_ASSERT("Not implemented module");
		}

		HWND WindowImpl::getWindowHandler()
		{
			HARD_ASSERT("Not implemented module");
			return nullptr;
		}
	}
}
#endif