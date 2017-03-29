#include <stdafx.h>
#include <engine/Context.h>
/////////////////////////////////////////////
#include <engine/app/Application.h>

#include <engine/ModuleDefinitions.h>
namespace engine
{
	struct ContextPrivate
	{
		std::vector<bool> moduls = std::vector<bool>(uint32_t(ContextModuleType::NumModulTypes), false);
		std::unique_ptr<Application> application;
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

	Application *Context::getApplication()
	{
		ASSERT(isInitialized());
		return _members->application.get();
	}

	Application *Context::getApplicationUnsafe()
	{
		return _members->application.get();
	}

	void Context::setApplication(std::unique_ptr<Application> application)
	{
		_members->application = std::move(application);
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
