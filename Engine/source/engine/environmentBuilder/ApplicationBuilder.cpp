#include <stdafx.h>

#include <engine/environmentBuilder/ApplicationBuilder.h>
///////////////////////////////////////

#include <engine/environmentBuilder/FileSystemBuilder.h>

#include <engine/Context.h>
#include <engine/ModuleDefinitions.h>

#include <engine/app/Application.h>
#include <engine/app/IApplicationParameter.h>
#include <engine/app/IMain.h>

#include <engine/app/glfw/ApplicationImpl.h>
#include <engine/app/sdl/ApplicationImpl.h>
#include <engine/app/winapi/ApplicationImpl.h>

namespace engine
{
	struct ApplicationBuilderPrivate
	{
		ContextModuleType windowModule;
	};

	ApplicationBuilder::ApplicationBuilder(const ContextModuleType windowModule)
		:_members(new ApplicationBuilderPrivate())
	{
		_members->windowModule = windowModule;
	}

	ApplicationBuilder::ApplicationBuilder(ApplicationBuilder&& o)
	{
		_members = o._members;
		o._members = nullptr;
	}

	ApplicationBuilder::~ApplicationBuilder()
	{
		delete _members;
	}

	FileSystemBuilder ApplicationBuilder::build(std::unique_ptr<IApplicationParameter> arguments, std::unique_ptr<IMain> main)
	{
		std::unique_ptr<Application> app = createApplication(std::move(arguments), std::move(main));
		FileSystemBuilder result(app.get(), _members->windowModule);
		BaseBuilder::setApplication(std::move(app));

		return result;
	}
	std::unique_ptr<Application> ApplicationBuilder::createApplication(std::unique_ptr<IApplicationParameter> arguments, std::unique_ptr<IMain> main)
	{
		std::unique_ptr<Application> result;
#if ENGINE_USE_GLFW
		HARD_ASSERT(_members->windowModule == ContextModuleType::Glfw);
		result = std::make_unique<glfw::ApplicationImpl>(std::move(arguments), std::move(main));
#elif ENGINE_USE_SDL
		HARD_ASSERT(_members->windowModule == ContextModuleType::Sdl);
		result = std::make_unique<sdl::ApplicationImpl>(std::move(arguments), std::move(main));
#elif ENGINE_USE_WINAPI
		HARD_ASSERT(_members->windowModule == ContextModuleType::WinApi);
		result = std::make_unique<winapi::ApplicationImpl>(std::move(arguments), std::move(main));
#else
		HARD_FAIL("Unknown window context module");
#endif
		return result;
	}
}
