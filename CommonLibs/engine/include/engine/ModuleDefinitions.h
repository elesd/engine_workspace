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
	/**@see ContextModule_traits*/
	template<>
	struct ContextModule_traits<ContextModuleType::Glfw>
	{
		/**Classification of the module*/
		static const ContextModuleClassification classification;
		/**Name of the module*/
		static const std::string name;
	};

    ///////////////////////////////////////////////////////////////

	/**@see ContextModule_traits*/
	template<>
	struct ContextModule_traits<ContextModuleType::Sdl>
	{
		/**Classification of the module*/
		static const ContextModuleClassification classification;
		/**Name of the module*/
		static const std::string name;
	};

	///////////////////////////////////////////////////////////////

	/**@see ContextModule_traits*/
	template<>
	struct ContextModule_traits<ContextModuleType::WinApi>
	{
		/**Classification of the module*/
		static const ContextModuleClassification classification;
		/**Name of the module*/
		static const std::string name;
	};


}
