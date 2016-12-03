#include "stdafx.h"

#include "engine/environmentBuilder/BaseBuilder.h"
////////////////////////////////
#include "engine/Context.h"
#include "engine/app/Application.h"
#include "engine/view/WindowManager.h"
namespace engine
{
	void BaseBuilder::setApplication(std::unique_ptr<Application> app)
	{
		Context::getInstance()->setApplication(std::move(app));
	}

	void BaseBuilder::setWindowManager(std::unique_ptr<WindowManager> manager)
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
