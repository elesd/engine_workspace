#include <stdafx.h>
#include <engine/events/sdl/EventManagerImpl.h>

#if ENGINE_USE_SDL
#include <engine/app/Application.h>

#include <engine/events/sdl/MouseImpl.h>
#include <engine/events/sdl/KeyboardImpl.h>
#include <engine/events/EventManager.h>

#include <engine/Context.h>

namespace engine
{
	namespace sdl
	{

		void EventManagerImpl::handleEvent(const SDL_KeyboardEvent& event)
		{
			std::vector<KeyboardImpl*> sources = findEventSource<KeyboardImpl>();
			if(!sources.empty())
			{
				sources[0]->handleEvent(event);
			}
		}

		void EventManagerImpl::handleEvent(const SDL_MouseMotionEvent& event)
		{
			std::vector<MouseImpl*> sources = findEventSource<MouseImpl>();
			if(!sources.empty())
			{
				sources[0]->handleMoveEvent(event);
			}
		}

		void EventManagerImpl::handleEvent(const SDL_MouseButtonEvent& event)
		{
			std::vector<MouseImpl*> sources = findEventSource<MouseImpl>();
			if(!sources.empty())
			{
				sources[0]->handleClickEvent(event);
			}
		}

		void EventManagerImpl::handleEvent(const SDL_MouseWheelEvent& event)
		{
			std::vector<MouseImpl*> sources = findEventSource<MouseImpl>();
			if(!sources.empty())
			{
				sources[0]->handleScrollEvent(event);
			}
		}

	}
}
#else 

#include <engine/events/sdl/empty/EventManagerImpl.cpp>

#endif
