#pragma once

namespace engine
{
	namespace winapi
	{
		/**WinApi Core module.*/
		class Core
		{
		public:
			/**
			* Initialize the module.
			* @returns Returns true when the initialization was successful. 
			*/
			static bool init();
		};
	}
}