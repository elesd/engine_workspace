#pragma once

#include "engine/utils/VersionBase.h"

namespace engine
{
	namespace version
	{
		/**
		* Class for version handling in the source code.
		*/
		class VersionDef
		{
		protected:
			/**Major version number*/
			const int major = 0;
			/**Minor version number*/
			const int minor = 1;
			/**Counter for the current version*/
			const int counter = 1;
			/** Creation year of the version.*/
			const std::string year = "17";
			/** Creation month of the version.*/
			const std::string month = "05";
			/** Creation day of the version.*/
			const std::string day = "21";
		};
		
		/**Creates a concrate version based on its definition.*/
		using Version = VersionBase<VersionDef>;
	}
}

#define ENGINE_USE_SDL 0
#define ENGINE_USE_GLFW 0
#define ENGINE_USE_WINAPI 1
