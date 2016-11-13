#include "stdafx.h"

#include "engine/environmentBuilder/ApplicationBuilder.h"
///////////////////////////////////////

#include "engine/environmentBuilder/WindowEnvironmentBuilder.h"

#include "engine/Context.h"
#include "engine/app/Application.h"
#include "engine/app/IApplicationParameter.h"
#include "engine/app/IMain.h"

namespace engine
{
	namespace environmentBuilder
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

		WindowEnvironmentBuilder ApplicationBuilder::build(std::unique_ptr<app::IApplicationParameter> arguments, std::unique_ptr<app::IMain> main)
		{
			std::unique_ptr<app::Application> app(new app::Application(std::move(arguments), std::move(main)));
			BaseBuilder::setApplication(std::move(app));

			return std::move(WindowEnvironmentBuilder(_members->windowModule));
		}



	}
}
