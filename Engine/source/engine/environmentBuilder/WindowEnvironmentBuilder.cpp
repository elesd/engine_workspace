#include "stdafx.h"
#include "engine/environmentBuilder/WindowEnvironmentBuilder.h"
////////////////////////////////////////////////////////////////

#include "engine/environmentBuilder/BuildFinalizer.h"

#include "engine/Context.h"
#include "engine/ModuleDefinitions.h"

#include "engine/modules/glfw/WindowManagerImpl.h"
#include "engine/modules/sdl/WindowManagerImpl.h"
#include "engine/modules/winapi/WindowManagerImpl.h"



namespace engine
{
	namespace environmentBuilder
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
			std::unique_ptr<view::WindowManager> manager;
			switch(_members->windowModule)
			{
				case ContextModuleType::Glfw: manager = createGlfwWindowManager(); break;
				case ContextModuleType::Sdl: manager = createSdlWindowManager(); break;
				case ContextModuleType::WinApi: manager = createWinApiWindowManager(); break;
			}
			ASSERT(manager);
			BaseBuilder::setWindowManager(std::move(manager));
			return BuildFinalizer();
		}

		std::unique_ptr<view::WindowManager> WindowEnvironmentBuilder::createGlfwWindowManager()
		{
			std::unique_ptr<view::WindowManager> result(new glfw::WindowManagerImpl());
			return result;
		}

		std::unique_ptr<view::WindowManager> WindowEnvironmentBuilder::createSdlWindowManager()
		{
			std::unique_ptr<view::WindowManager> result(new sdl::WindowManagerImpl());
			return result;
		}
		std::unique_ptr<view::WindowManager> WindowEnvironmentBuilder::createWinApiWindowManager()
		{
			std::unique_ptr<view::WindowManager> result(new winapi::WindowManagerImpl());
			return result;
		}
	}
}
