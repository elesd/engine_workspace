#include <stdafx.h>

#include <engine/environmentBuilder/BaseBuilder.h>
////////////////////////////////
#include <engine/Context.h>
#include <engine/app/Application.h>
#include <engine/events/EventManager.h>
#include <engine/view/WindowManager.h>
namespace engine
{
	void BaseBuilder::setApplication(std::unique_ptr<Application> app)
	{
		Context::getInstance()->setApplication(std::move(app));
	}

	void BaseBuilder::setWindowManager(std::unique_ptr<WindowManager> manager)
	{
		Context::getInstance()->getApplicationUnsafe()->setWindowManager(std::move(manager));
	}

	void BaseBuilder::addModule(const ContextModuleType value)
	{
		Context::getInstance()->getModuls()[uint32_t(value)] = true;
	}

	void BaseBuilder::setInitialized()
	{
		Context::getInstance()->setInitialized();
	}

	void BaseBuilder::setConsole(std::unique_ptr<Console>&& console)
	{
		Context::getInstance()->setConsole(std::move(console));
	}

	void BaseBuilder::setFileSystem(Application *app, std::unique_ptr<FileSystem> &&fileSystem)
	{
		app->setFileSystem(std::move(fileSystem));
	}

}
