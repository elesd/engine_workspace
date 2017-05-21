#include <stdafx.h>
#if ENGINE_USE_SDL
#include <engine/modules/sdl/Core.h>
/////////////////////////////////////////////////////

extern "C"
{
#	include <SDL2/SDL.h>
}

namespace engine
{
	namespace sdl
	{
		bool Core::init()
		{
			return SDL_Init(SDL_INIT_EVERYTHING) == 0;
		}
	}
}
#else 

#include <engine/modules/sdl/empty/Core.cpp>
#endif