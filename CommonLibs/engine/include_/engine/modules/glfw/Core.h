#pragma once

namespace engine
{
	namespace glfw
	{
		/**
		* Glfw module core module.
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