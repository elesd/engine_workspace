#include <stdafx.h>

#include <engine/ModuleDefinitions.h>

namespace engine
{

    ////////////////////////////////////////////////////////

    const ContextModuleClassification ContextModule_traits<ContextModuleType::Glfw>::classification = ContextModuleClassification::Window;
	const std::string ContextModule_traits<ContextModuleType::Glfw>::name = "Glfw";

    ////////////////////////////////////////////////////////

    const ContextModuleClassification ContextModule_traits<ContextModuleType::Sdl>::classification = ContextModuleClassification::Window;
	const std::string ContextModule_traits<ContextModuleType::Sdl>::name = "Sdl";

    ////////////////////////////////////////////////////////

    const ContextModuleClassification ContextModule_traits<ContextModuleType::WinApi>::classification = ContextModuleClassification::Window;
	const std::string ContextModule_traits<ContextModuleType::WinApi>::name = "WinApi";

    ////////////////////////////////////////////////////////

}
