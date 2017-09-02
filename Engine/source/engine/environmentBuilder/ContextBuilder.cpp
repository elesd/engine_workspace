#include <stdafx.h>

#include <engine/environmentBuilder/ContextBuilder.h>
////////////////////////////////////////////////////

#include <engine/environmentBuilder/ApplicationBuilder.h>
#include <engine/Context.h>
#include <engine/ModuleDefinitions.h>

#include <engine/modules/glfw/Core.h>
#include <engine/modules/glew/Core.h>
#include <engine/modules/sdl/Core.h>
#include <engine/modules/winapi/Core.h>

#include <engine/exceptions/LogicalErrors.h>

#include <engine/view/Console.h>
#include <engine/view/winapi/ConsoleImpl.h>

namespace engine
{
	struct ContextBuilderPrivate
	{
		using ModuleContainer = std::map<ContextModuleClassification, std::vector<ContextModuleType>>;
		ModuleContainer modules;
	};

	ContextBuilder::ContextBuilder(const std::vector<ContextModuleType> &modules)
		:_members(new ContextBuilderPrivate())
	{
		for(const ContextModuleType &type : modules)
		{
			switch(type)
			{
				case ContextModuleType::Glfw:
				_members->modules[ContextModule_traits<ContextModuleType::Glfw>::classification].push_back(type);
				_members->modules[ContextModule_traits<ContextModuleType::Glew>::classification].push_back(ContextModuleType::Glew);
				break;
				case ContextModuleType::Sdl:
				_members->modules[ContextModule_traits<ContextModuleType::Sdl>::classification].push_back(type);
				_members->modules[ContextModule_traits<ContextModuleType::Glew>::classification].push_back(ContextModuleType::Glew);
				break;
				case ContextModuleType::WinApi:
				_members->modules[ContextModule_traits<ContextModuleType::WinApi>::classification].push_back(type);
				break;
				default: FAIL("Unknown module type"); break;
			}
		}
	}

	ContextBuilder::ContextBuilder(ContextBuilder &&o)
	{
		_members = o._members;
		o._members = nullptr;
	}

	ContextBuilder::~ContextBuilder()
	{
		delete _members;
	}

	ApplicationBuilder ContextBuilder::buildForApplication()
	{
		if(_members->modules[ContextModuleClassification::Window].size() < 1)
			throw InitializationError("Window manager module is not unique");
		if(_members->modules[ContextModuleClassification::Window].size() == 0)
			throw InitializationError("Window manager module is not defined");

		initContext();
		return ApplicationBuilder(_members->modules[ContextModuleClassification::Window].back());
	}

	void ContextBuilder::initContext()
	{
		Context::createInstance();
		initConsole();
		for(const ContextModuleType &type : _members->modules[ContextModuleClassification::Window])
		{
			initModule(type);
		}
		for(const ContextModuleType &type : _members->modules[ContextModuleClassification::Utils])
		{
			initModule(type);
		}
	}

	void ContextBuilder::initConsole()
	{
		std::unique_ptr<Console> console;
#if ENGINE_USE_WINAPI
		HARD_ASSERT(_members->modules[ContextModuleClassification::Window].front() == ContextModuleType::WinApi);
		console = std::make_unique<winapi::ConsoleImpl>();
#else
		console = std::make_unique<Console>();
#endif
		setConsole(std::move(console));
	}

	void ContextBuilder::initModule(const ContextModuleType type)
	{
		bool res = false;
		std::string moduleName = "Unknown";

		switch(type)
		{
			case ContextModuleType::Glfw:
#if ENGINE_USE_GLFW
			res = glfw::Core::init();
			moduleName = ContextModule_traits<ContextModuleType::Glfw>::name;
#else
			INACTIVE_MODULE_ERROR();
#endif
			break;
			case ContextModuleType::Sdl:
#if ENGINE_USE_SDL
			res = sdl::Core::init();
			moduleName = ContextModule_traits<ContextModuleType::Sdl>::name;
#else
				INACTIVE_MODULE_ERROR();
#endif
			break;
			case ContextModuleType::WinApi:
#if ENGINE_USE_WINAPI
			res = winapi::Core::init();
			moduleName = ContextModule_traits<ContextModuleType::WinApi>::name;
#else
				INACTIVE_MODULE_ERROR();
#endif
			break;
			case ContextModuleType::Glew:
#if ENGINE_USE_GLEW
			res = glew::Core::init();
			moduleName = ContextModule_traits<ContextModuleType::Glew>::name;
#else
				INACTIVE_MODULE_ERROR();
#endif
			break;
			default:
			FAIL("Unknown module");
			res = false;
		}
		if(!res)
			throw InitializationError("Module cannot be initialized: " + moduleName);
		BaseBuilder::addModule(type);
	}
}
