#include "stdafx.h"
#if ENGINE_USE_SDL == 0
#include "engine/modules/sdl/WindowImpl.h"
/////////////////////////////////////////

namespace engine
{
	namespace sdl
	{

		WindowImpl::WindowImpl(SDL_Window *, const view::WindowParameter &, const std::string &)
			: view::Window()
		{
			HARD_ASSERT("Not implemented module");
		}

		WindowImpl::WindowImpl(SDL_Window *, const std::string &)
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

		SDL_Window *WindowImpl::getSDLWindow()
		{
			HARD_ASSERT("Not implemented module");
			return nullptr;
		}
	}
}
#endif