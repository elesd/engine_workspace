#include "stdafx.h"

#include "engine/environmentBuilder/BaseBuilder.h"
////////////////////////////////
#include "engine/Context.h"
#include "engine/app/Application.h"
#include "engine/view/WindowManager.h"
namespace engine
{
	namespace environmentBuilder
	{
		void BaseBuilder::setApplication(std::unique_ptr<app::Application> app)
		{
			Context::getInstance()->setApplication(std::move(app));
		}

		void BaseBuilder::setWindowManager(std::unique_ptr<view::WindowManager> manager)
		{
			Context::getInstance()->setWindowManager(std::move(manager));
		}

		void BaseBuilder::addModule(const ContextModuleType value)
		{
			Context::getInstance()->getModuls()[uint32_t(value)] = true;
		}

		void BaseBuilder::setInitialized()
		{
			Context::getInstance()->setInitialized();
		}
	}
}
