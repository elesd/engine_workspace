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


namespace engine
{
	struct ContextBuilderPrivate
	{
		typedef std::map<ContextModuleClassification, std::vector<ContextModuleType>> ModuleContainer;
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
		for(const ContextModuleType &type : _members->modules[ContextModuleClassification::Window])
		{
			initModule(type);
		}
		for(const ContextModuleType &type : _members->modules[ContextModuleClassification::Utils])
		{
			initModule(type);
		}
	}

	void ContextBuilder::initModule(const ContextModuleType type)
	{
		bool res = false;
		std::string moduleName = "Unknown";
		switch(type)
		{
			case ContextModuleType::Glfw:
			res = glfw::Core::init();
			moduleName = ContextModule_traits<ContextModuleType::Glfw>::name;
			break;
			case ContextModuleType::Sdl:
			res = sdl::Core::init();
			moduleName = ContextModule_traits<ContextModuleType::Sdl>::name;
			break;
			case ContextModuleType::WinApi:
			res = winapi::Core::init();
			moduleName = ContextModule_traits<ContextModuleType::WinApi>::name;
			break;
			case ContextModuleType::Glew:
			res = glew::Core::init();
			moduleName = ContextModule_traits<ContextModuleType::Glew>::name;
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
