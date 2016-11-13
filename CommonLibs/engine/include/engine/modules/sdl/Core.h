#pragma once

namespace engine
{
	namespace sdl
	{	
		/**
		* Sdl module core module.
		*/
		class Core
		{
		public:
			/**
			* Initialize the module.
			* @return True if the init was successfull.
			*/
			static bool init();
		};
	}
}