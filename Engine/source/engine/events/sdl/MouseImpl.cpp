#include <stdafx.h>
#include <engine/events/sdl/MouseImpl.h>
///////////////////////////////////////////////////////////////////////////////
#if ENGINE_USE_SDL
#include <engine/Context.h>
#include <engine/events/EventManager.h>

#include <SDL2/SDL.h>

namespace engine
{
	namespace sdl
	{
		void MouseImpl::handleMoveEvent(const SDL_MouseMotionEvent& event)
		{
			onMouseMoved(event.x, event.y);
			moved.emit(event.x, event.y);
		}

		void MouseImpl::handleClickEvent(const SDL_MouseButtonEvent& event)
		{
			if(event.type == SDL_MOUSEBUTTONDOWN)
			{
				switch(event.button)
				{
					case SDL_BUTTON_LEFT:
						onLeftButtonPressed();
						leftButtonPressed.emit(event.x, event.y);
						break;
					case SDL_BUTTON_RIGHT:
						onRightButtonPressed();
						rightButtonPressed.emit(event.x, event.y);
						break;
					case SDL_BUTTON_MIDDLE:
						onMiddleButtonPressed();
						middleButtonPressed.emit(event.x, event.y);
						break;
				}
			}
			else if(event.type == SDL_MOUSEBUTTONUP)
			{

				switch(event.button)
				{
					case SDL_BUTTON_LEFT:
						onLeftButtonReleased();
						leftButtonReleased.emit(event.x, event.y);
						break;
					case SDL_BUTTON_RIGHT:
						onRightButtonReleased();
						rightButtonReleased.emit(event.x, event.y);
						break;
					case SDL_BUTTON_MIDDLE:
						onMiddleButtonReleased();
						middleButtonReleased.emit(event.x, event.y);
						break;
				}
			}
		}

		void MouseImpl::handleScrollEvent(const SDL_MouseWheelEvent& event)
		{
			ScreenSpacePosition pos = getPosition();
			scrolled.emit(pos.x, pos.y, event.y);
		}
	}
}

#endif
