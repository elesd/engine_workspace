#include "stdafx.h"
#if ENGINE_USE_SDL
#include "engine/modules/sdl/WindowImpl.h"
/////////////////////////////////////////

#include "SDL2/SDL.h"

namespace engine
{
	namespace sdl
	{
		struct WindowImplPrivate
		{
			SDL_Window *window = nullptr;
			std::string title;
		};

		WindowImpl::WindowImpl(SDL_Window *window, const WindowParameter &parameters, const std::string &title)
			: Window(parameters),
			_members(new WindowImplPrivate())
		{
			_members->window = window;
			_members->title = title;
			_parameters = parameters;

			ASSERT(_members->window != nullptr);
			SDL_SetWindowPosition(_members->window, _parameters.x, _parameters.y);
			SDL_SetWindowSize(_members->window, _parameters.width, _parameters.height);

		}

		WindowImpl::WindowImpl(SDL_Window *window, const std::string &title)
			: Window(),
			_members(new WindowImplPrivate())
		{
			_members->window = window;
			_members->title = title;
		}

		WindowImpl::~WindowImpl()
		{
			if(_members && _members->window)
			{
				SDL_DestroyWindow(_members->window);
			}
			delete _members;
		}

		WindowImpl::operator bool() const
		{
			return _members->window != nullptr;
		}

		void WindowImpl::setPositionImp(int32_t x, int32_t y)
		{
			ASSERT(_members->window != nullptr);
			SDL_SetWindowPosition(_members->window, x, y);

		}

		void WindowImpl::setWidthImpl(uint32_t width)
		{
			ASSERT(_members->window != nullptr);
			SDL_SetWindowSize(_members->window, width, _parameters.height);
		}

		void WindowImpl::setHeightImpl(uint32_t height)
		{
			ASSERT(_members->window != nullptr);
			SDL_SetWindowSize(_members->window, _parameters.width, height);

		}

		void WindowImpl::setSizeImpl(uint32_t width, uint32_t height)
		{
			ASSERT(_members->window != nullptr);
			SDL_SetWindowSize(_members->window, width, height);
		}

		SDL_Window *WindowImpl::getSDLWindow()
		{
			return _members->window;
		}

	}
}
#endif