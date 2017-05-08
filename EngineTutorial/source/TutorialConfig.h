#pragma once

#include "engine/utils/VersionBase.h"

namespace version
{
	class VersionDef
	{
	protected:
		const int major = 0;
		const int minor = 1;
		const int counter = 1;
		const std::string year = "17";
		const std::string month = "05";
		const std::string day = "08";
	};
		
	using Version = engine::VersionBase<VersionDef>;
}


#define TUTORIAL_USE_SDL 0
#define TUTORIAL_USE_GLFW 1
#define TUTORIAL_USE_WINAPI 0
