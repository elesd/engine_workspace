#include "stdafx.h"

#include "engine/environmentBuilder/ContextBuilder.h"
////////////////////////////////////////////////////

#include "engine/environmentBuilder/ApplicationBuilder.h"
#include "engine/Context.h"
#include "engine/ModuleDefinitions.h"
#include "engine/modules/glfw/Core.h"
#include "engine/modules/sdl/Core.h"
#include "engine/modules/winapi/Core.h"

namespace engine
{
	namespace environmentBuilder
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
					case ContextModuleType::Glfw: _members->modules[ContextModule_traits<ContextModuleType::Glfw>::classification].push_back(type); break;
					case ContextModuleType::Sdl: _members->modules[ContextModule_traits<ContextModuleType::Sdl>::classification].push_back(type); break;
					case ContextModuleType::WinApi: _members->modules[ContextModule_traits<ContextModuleType::WinApi>::classification].push_back(type); break;
					default: FAIL("Unknown module type"); break;
				}
			}
			// When there is more than one or there is no window manager module is defined
			ASSERT(_members->modules[ContextModuleClassification::Window].size() == 1);
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
			initContext();
			return ApplicationBuilder(_members->modules[ContextModuleClassification::Window].back());
		}

		void ContextBuilder::initContext()
		{
			Context::createInstance();
			for(const auto &pair : _members->modules)
			{
				for(const ContextModuleType &type : pair.second)
				{
					initModule(type);
				}
			}
		}

		void ContextBuilder::initModule(const ContextModuleType type)
		{
			bool res = false;
			switch(type)
			{
				case ContextModuleType::Glfw: res = glfw::Core::init(); break;
				case ContextModuleType::Sdl: res = sdl::Core::init(); break;
				case ContextModuleType::WinApi: res = winapi::Core::init(); break;
			}
			ASSERT(res);
			BaseBuilder::addModule(type);
		}
	}
}
