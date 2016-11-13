#include <stdafx.h>
#include "engine/Context.h"
/////////////////////////////////////////////
#include "engine/app/Application.h"
#include "engine/view/WindowManager.h"

#include "engine/ModuleDefinitions.h"
namespace engine
{
	struct ContextPrivate
	{
		std::vector<bool> moduls = std::vector<bool>(uint32_t(ContextModuleType::NumModulTypes), false);
		std::unique_ptr<app::Application> application;
		std::unique_ptr<view::WindowManager> windowManager;
		bool initialized = false;
	};

	Context::Context()
		:_members(new ContextPrivate())
	{

	}

	Context::~Context()
	{
		delete _members;
	}

	app::Application *Context::getApplication()
	{
		ASSERT(isInitialized());
		return _members->application.get();
	}

	view::WindowManager *Context::getWindowManager()
	{
		ASSERT(isInitialized());
		return _members->windowManager.get();
	}

	void Context::setApplication(std::unique_ptr<app::Application> application)
	{
		_members->application = std::move(application);
	}

	void Context::setWindowManager(std::unique_ptr<view::WindowManager> windowManager)
	{
		_members->windowManager = std::move(windowManager);
	}

	std::vector<bool> &Context::getModuls()
	{
		return _members->moduls;
	}

	void Context::setInitialized()
	{
		ASSERT(!isInitialized());
		_members->initialized = true;
	}

	bool Context::isInitialized() const
	{
		return _members->initialized;
	}
}
