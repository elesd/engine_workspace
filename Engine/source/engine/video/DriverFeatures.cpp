#include <stdafx.h>
#include <engine/video/DriverFeatures.h>
///////////////////////////////////////////////////////////////////////////////

namespace engine
{
	//////////////////////////////////////////////////////////////////////////////

	std::array<bool, uint32_t(Feature::Num)> DriverFeatureSet<ContextModuleType::Glfw>::features 
	{
		false // RightHandedMath
	};

	//////////////////////////////////////////////////////////////////////////////

	std::array<bool, uint32_t(Feature::Num)> DriverFeatureSet<ContextModuleType::Sdl>::features 
	{
		false // RightHandedMath
	};

	//////////////////////////////////////////////////////////////////////////////

	std::array<bool, uint32_t(Feature::Num)> DriverFeatureSet<ContextModuleType::WinApi>::features =
	{
		true // RightHandedMath
	};
}
