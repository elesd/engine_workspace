#include "stdafx.h"

#include "engine/ModuleDefinitions.h"

namespace engine
{

    ////////////////////////////////////////////////////////

    const ContextModuleClassification ContextModule_traits<ContextModuleType::Glfw>::classification = ContextModuleClassification::Window;

    ////////////////////////////////////////////////////////

    const ContextModuleClassification ContextModule_traits<ContextModuleType::Sdl>::classification = ContextModuleClassification::Window;

    ////////////////////////////////////////////////////////

    const ContextModuleClassification ContextModule_traits<ContextModuleType::WinApi>::classification = ContextModuleClassification::Window;

    ////////////////////////////////////////////////////////

}
