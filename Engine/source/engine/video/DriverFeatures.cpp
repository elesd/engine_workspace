#include <stdafx.h>
#include <engine/video/DriverFeatures.h>
///////////////////////////////////////////////////////////////////////////////

namespace engine
{
	NDCType DriverFeaturesHelper::getNDCType(ContextModuleType type)
	{
		switch(type)
		{
			case engine::ContextModuleType::Glfw:
				return DriverFeatures<ContextModuleType::Glfw>::ndcType;
				break;
			case engine::ContextModuleType::Sdl:
				return DriverFeatures<ContextModuleType::Sdl>::ndcType;
				break;
			case engine::ContextModuleType::WinApi:
				return DriverFeatures<ContextModuleType::WinApi>::ndcType;
				break;
			case engine::ContextModuleType::Glew:
			case engine::ContextModuleType::NumModulTypes:
			default:
				FAIL("Not Window module");
				break;
		}
	}

	//////////////////////////////////////////////////////////////////////////////

	std::array<bool, uint32_t(Feature::Num)> DriverFeatures<ContextModuleType::Glfw>::features =
	{
		false // RightHandedMath
	};

	//////////////////////////////////////////////////////////////////////////////

	std::array<bool, uint32_t(Feature::Num)> DriverFeatures<ContextModuleType::Sdl>::features =
	{
		false // RightHandedMath
	};

	//////////////////////////////////////////////////////////////////////////////

	std::array<bool, uint32_t(Feature::Num)> DriverFeatures<ContextModuleType::WinApi>::features =
	{
		true // RightHandedMath
	};
}