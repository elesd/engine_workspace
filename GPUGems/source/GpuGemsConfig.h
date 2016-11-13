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
		const std::string year = "16";
		const std::string month = "11";
		const std::string day = "13";
	};
		
	using Version = engine::utils::VersionBase<VersionDef>;
}


#define USE_SDL 0
#define USE_GLWF 0
#define USE_WINAPI 1
