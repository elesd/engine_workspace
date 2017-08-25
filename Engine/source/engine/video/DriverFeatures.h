#pragma once

#include <engine/ModuleDefinitions.h>

namespace engine
{

	enum class Feature
	{
		RightHandedMath, 
		Num
	};

	enum class NDCType
	{
		OpenGl,
		DirectX
	};

	template<class FeatureSet>
	struct FeatureQuerier : FeatureSet
	{
		static bool hasFeature(Feature f) { return features[uint32_t(f)]; }
	};

	template<ContextModuleType type>
	struct DriverFeatureSet;

	//////////////////////////////////////////////////////////////////////////////

	template<>
	struct DriverFeatureSet<ContextModuleType::Sdl>
	{
		static const NDCType ndcType = NDCType::OpenGl;
		static std::array<bool, uint32_t(Feature::Num)> features;
	};

	//////////////////////////////////////////////////////////////////////////////

	template<>
	struct DriverFeatureSet<ContextModuleType::Glfw>
	{
		static const NDCType ndcType = NDCType::OpenGl;
		static std::array<bool, uint32_t(Feature::Num)> features;
	};

	//////////////////////////////////////////////////////////////////////////////

	template<>
	struct DriverFeatureSet<ContextModuleType::WinApi>
	{
		static const NDCType ndcType = NDCType::DirectX;
		static std::array<bool, uint32_t(Feature::Num)> features;
	};

	//////////////////////////////////////////////////////////////////////////////

	template<ContextModuleType Type>
	struct DriverFeatures : FeatureQuerier<DriverFeatureSet<Type>>
	{
	};
}

#include <engine/video/DriverFeatures.hpp>

namespace engine
{
#if ENGINE_USE_GLFW
	using CurrentDriverFeatures = DriverFeatures<ContextModuleType::Glfw>;
#elif ENGINE_USE_SDL
	using CurrentDriverFeatures = DriverFeatures<ContextModuleType::Glfw>;
#elif ENGINE_USE_WINAPI
	using CurrentDriverFeatures = DriverFeatures<ContextModuleType::Glfw>;
#else
#error Unknown window module
#endif
}
