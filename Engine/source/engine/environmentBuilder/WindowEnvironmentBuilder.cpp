#include <stdafx.h>
#include <engine/environmentBuilder/WindowEnvironmentBuilder.h>
////////////////////////////////////////////////////////////////

#include <engine/environmentBuilder/BuildFinalizer.h>

#include <engine/exceptions/LogicalErrors.h>

#include <engine/Context.h>
#include <engine/ModuleDefinitions.h>

#include <engine/video/Driver.h>

#include <engine/view/glfw/WindowManagerImpl.h>
#include <engine/view/sdl/WindowManagerImpl.h>
#include <engine/view/winapi/WindowManagerImpl.h>



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

	BuildFinalizer WindowEnvironmentBuilder::build(const DriverContextParameters& driverContextParameters)
	{
		std::unique_ptr<WindowManager> manager;
		switch(_members->windowModule)
		{
			case ContextModuleType::Glfw: manager = createGlfwWindowManager(driverContextParameters); break;
			case ContextModuleType::Sdl: manager = createSdlWindowManager(driverContextParameters); break;
			case ContextModuleType::WinApi: manager = createWinApiWindowManager(driverContextParameters); break;
		}
		if(!manager)
			throw InitializationError("Unhandled window module");
		BaseBuilder::setWindowManager(std::move(manager));
		return BuildFinalizer();
	}

	std::unique_ptr<WindowManager> WindowEnvironmentBuilder::createGlfwWindowManager(const DriverContextParameters& driverContextParameters)
	{
		std::unique_ptr<WindowManager> result(new glfw::WindowManagerImpl(driverContextParameters));
		return result;
	}

	std::unique_ptr<WindowManager> WindowEnvironmentBuilder::createSdlWindowManager(const DriverContextParameters& driverContextParameters)
	{
		std::unique_ptr<WindowManager> result(new sdl::WindowManagerImpl(driverContextParameters));
		return result;
	}
	std::unique_ptr<WindowManager> WindowEnvironmentBuilder::createWinApiWindowManager(const DriverContextParameters& driverContextParameters)
	{
		std::unique_ptr<WindowManager> result(new winapi::WindowManagerImpl(driverContextParameters));
		return result;
	}
}
