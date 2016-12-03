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
		const std::string month = "12";
		const std::string day = "03";
	};
		
	using Version = engine::VersionBase<VersionDef>;
}



