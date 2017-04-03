#pragma once

namespace engine
{
	/**
	* Known modules' type
	*/
	enum class ContextModuleType
	{
		Glfw,
		Sdl,
		WinApi,
		NumModulTypes
	};

	/**
	* This enumeration contains the classification types of the different known modules.
	* @see ContextModuleType
	*/
	enum class ContextModuleClassification
	{
		Window,
		Utils
	};

	/**
	* Meta data for module types.
	*/
	template<ContextModuleType type>
	struct ContextModule_traits
	{};

    ///////////////////////////////////////////////////////////////
	template<>
	struct ContextModule_traits<ContextModuleType::Glfw>
	{
		static const ContextModuleClassification classification;
		static const std::string name;
	};

    ///////////////////////////////////////////////////////////////

	template<>
	struct ContextModule_traits<ContextModuleType::Sdl>
	{
		static const ContextModuleClassification classification;
		static const std::string name;
	};

	///////////////////////////////////////////////////////////////
	template<>
	struct ContextModule_traits<ContextModuleType::WinApi>
	{
		static const ContextModuleClassification classification;
		static const std::string name;
	};


}
