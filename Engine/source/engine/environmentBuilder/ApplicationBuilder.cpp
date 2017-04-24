#include <stdafx.h>

#include <engine/environmentBuilder/ApplicationBuilder.h>
///////////////////////////////////////

#include <engine/environmentBuilder/EventBuilder.h>

#include <engine/Context.h>
#include <engine/ModuleDefinitions.h>

#include <engine/app/Application.h>
#include <engine/app/IApplicationParameter.h>
#include <engine/app/IMain.h>

#include <engine/app/glfw/ApplicationImpl.h>
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

	EventBuilder ApplicationBuilder::build(std::unique_ptr<IApplicationParameter> arguments, std::unique_ptr<IMain> main)
	{
		std::unique_ptr<Application> app = createApplication(std::move(arguments), std::move(main));
		BaseBuilder::setApplication(std::move(app));

		return EventBuilder(_members->windowModule);
	}
	std::unique_ptr<Application> ApplicationBuilder::createApplication(std::unique_ptr<IApplicationParameter> arguments, std::unique_ptr<IMain> main)
	{
		std::unique_ptr<Application> result;
		switch(_members->windowModule)
		{
			case ContextModuleType::WinApi: result = std::make_unique<winapi::ApplicationImpl>(std::move(arguments), std::move(main)); break;
			case ContextModuleType::Glfw:	result = std::make_unique<glfw::ApplicationImpl>(std::move(arguments), std::move(main)); break;
				// TODO
			case ContextModuleType::Sdl:
			default:HARD_FAIL("Not implemented"); break;
		}
		return result;
	}
}
