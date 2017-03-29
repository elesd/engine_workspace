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
			const std::string year = "17";
			const std::string month = "03";
			const std::string day = "29";
		};
		
		using Version = VersionBase<VersionDef>;
	}
}

#define ENGINE_USE_SDL 0
#define ENGINE_USE_GLFW 0
#define ENGINE_USE_WINAPI 1
