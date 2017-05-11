#include <stdafx.h>
#include <engine/app/sdl/ApplicationImpl.h>
///////////////////////////////////////////////////////////////////////////////

#if ENGINE_USE_SDL

#include <engine/app/IMain.h>
#include <engine/app/IApplicationParameter.h>

#include <engine/events/sdl/EventManagerImpl.h>

#include <engine/view/sdl/WindowManagerImpl.h>
#include <engine/view/sdl/WindowImpl.h>

#include <SDL2/SDL.h>

namespace engine
{
	namespace sdl
	{
		ApplicationImpl::ApplicationImpl(std::unique_ptr<IApplicationParameter> arguments, std::unique_ptr<IMain> main)
			:Application(std::move(arguments), std::move(main))
		{
		}

		void ApplicationImpl::updateImpl()
		{
			SDL_Event event;
			WindowManagerImpl *windowManager = static_cast<WindowManagerImpl*>(getWindowManager());
			while(SDL_PollEvent(&event))
			{
				switch(event.type)
				{
					case SDL_KEYDOWN:
					case SDL_KEYUP:
					{
						WindowImpl* window = windowManager->findWindowBySDLId(event.key.windowID);
						if(window)
						{
							static_cast<EventManagerImpl*>(window->getEventManager())->handleEvent(event.key);
						}
					}
					break;
					case SDL_MOUSEMOTION:
					{
						WindowImpl* window = windowManager->findWindowBySDLId(event.motion.windowID);
						if(window)
						{
							static_cast<EventManagerImpl*>(window->getEventManager())->handleEvent(event.motion);
						}
					}
					break;
					case SDL_MOUSEBUTTONDOWN:
					case SDL_MOUSEBUTTONUP:
					{
						WindowImpl* window = windowManager->findWindowBySDLId(event.button.windowID);
						if(window)
						{
							static_cast<EventManagerImpl*>(window->getEventManager())->handleEvent(event.button);
						}
					}
					break;
					case SDL_MOUSEWHEEL:
					{
						WindowImpl* window = windowManager->findWindowBySDLId(event.wheel.windowID);
						if(window)
						{
							static_cast<EventManagerImpl*>(window->getEventManager())->handleEvent(event.wheel);
						}
					}
					break;
					case SDL_QUIT:
						stop();
						break;
					case SDL_WINDOWEVENT:
						windowManager->handleEvent(event.window);
						break;

				}
			}
		}
	}
}

#endif