#pragma once

#include "engine/utils/VersionBase.h"

namespace engine
{
	namespace version
	{
		class VersionDef
		{
		protected:
			const int major = 0;
			const int minor = 1;
			const int counter = 1;
			const std::string year = "16";
			const std::string month = "12";
			const std::string day = "03";
		};
		
		using Version = VersionBase<VersionDef>;
	}
}

#define ENGINE_USE_SDL 0
#define ENGINE_USE_GLFW 1
#define ENGINE_USE_WINAPI 0
