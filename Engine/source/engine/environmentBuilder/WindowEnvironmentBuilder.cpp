#include "stdafx.h"
#include "engine/environmentBuilder/WindowEnvironmentBuilder.h"
////////////////////////////////////////////////////////////////

#include "engine/environmentBuilder/BuildFinalizer.h"

#include "engine/exceptions/LogicalErrors.h"

#include "engine/Context.h"
#include "engine/ModuleDefinitions.h"

#include "engine/view/glfw/WindowManagerImpl.h"
#include "engine/view/sdl/WindowManagerImpl.h"
#include "engine/view/winapi/WindowManagerImpl.h"



namespace engine
{
	struct WindowEnvironmentBuilderPrivate
	{
		ContextModuleType windowModule;
	};

	WindowEnvironmentBuilder::WindowEnvironmentBuilder(const ContextModuleType windowModule)
		:_members(new WindowEnvironmentBuilderPrivate())
	{
		_members->windowModule = windowModule;
	}

	WindowEnvironmentBuilder::~WindowEnvironmentBuilder()
	{
		delete _members;
	}

	WindowEnvironmentBuilder::WindowEnvironmentBuilder(WindowEnvironmentBuilder &&o)
	{
		this->_members = o._members;
		o._members = nullptr;
	}

	BuildFinalizer WindowEnvironmentBuilder::build()
	{
		std::unique_ptr<WindowManager> manager;
		switch(_members->windowModule)
		{
			case ContextModuleType::Glfw: manager = createGlfwWindowManager(); break;
			case ContextModuleType::Sdl: manager = createSdlWindowManager(); break;
			case ContextModuleType::WinApi: manager = createWinApiWindowManager(); break;
		}
		if(!manager)
			throw InitializationError("Unhandled window module");
		BaseBuilder::setWindowManager(std::move(manager));
		return BuildFinalizer();
	}

	std::unique_ptr<WindowManager> WindowEnvironmentBuilder::createGlfwWindowManager()
	{
		std::unique_ptr<WindowManager> result(new glfw::WindowManagerImpl());
		return result;
	}

	std::unique_ptr<WindowManager> WindowEnvironmentBuilder::createSdlWindowManager()
	{
		std::unique_ptr<WindowManager> result(new sdl::WindowManagerImpl());
		return result;
	}
	std::unique_ptr<WindowManager> WindowEnvironmentBuilder::createWinApiWindowManager()
	{
		std::unique_ptr<WindowManager> result(new winapi::WindowManagerImpl());
		return result;
	}
}
