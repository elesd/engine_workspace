#include <stdafx.h>
#if ENGINE_USE_SDL
#include <engine/view/sdl/WindowImpl.h>
/////////////////////////////////////////

#include <engine/view/WindowManager.h>

#include <SDL2/SDL.h>

namespace engine
{
	namespace sdl
	{
		struct WindowImplPrivate
		{
			SDL_Window *window = nullptr;
			std::string title;
		};

		WindowImpl::WindowImpl(WindowManager *windowManager, SDL_Window *window, const WindowParameter &parameters, const std::string &title)
			: Window(windowManager, parameters),
			_members(new WindowImplPrivate())
		{
			_members->window = window;
			_members->title = title;
			_parameters = parameters;

			ASSERT(_members->window != nullptr);
			SDL_SetWindowPosition(_members->window, _parameters.x, _parameters.y);
			SDL_SetWindowSize(_members->window, _parameters.width, _parameters.height);

		}

		WindowImpl::WindowImpl(WindowManager *windowManager, SDL_Window *window, const std::string &title)
			: Window(windowManager),
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

		void WindowImpl::handleEvent(const SDL_WindowEvent& event)
		{
			switch(event.event)
			{
				case SDL_WINDOWEVENT_MOVED:
					windowMoved.emit(event.data1, event.data2);
					break;
				case SDL_WINDOWEVENT_SIZE_CHANGED:
					windowSizeChanged.emit(event.data1, event.data2);
					break;
				case SDL_WINDOWEVENT_FOCUS_GAINED:
					windowInFocus.emit();
					break;
				case SDL_WINDOWEVENT_FOCUS_LOST:
					windowOutFocus.emit();
					break;
				case SDL_WINDOWEVENT_CLOSE:
					windowClosed.emit();
					getWindowManager()->windowClosed(this);
					break;
			}
		}
	}
}

#endif