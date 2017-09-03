#include <stdafx.h>
#include <engine/Context.h>
/////////////////////////////////////////////
#include <engine/app/Application.h>

#include <engine/view/Console.h>

#include <engine/ModuleDefinitions.h>

namespace engine
{
	struct ContextPrivate
	{
		std::vector<bool> moduls = std::vector<bool>(uint32_t(ContextModuleType::NumModulTypes), false);
		std::unique_ptr<Console> console;
		std::unique_ptr<Application> application;
		bool initialized = false;
	};

	Application* Context::application()
	{
		if(!hasInstance())
		{
			return nullptr;
		}
		
		return getInstance()->getApplication();
	}

	Console* Context::console()
	{
		if(!hasInstance())
		{
			return nullptr;
		}
		return getInstance()->getConsole();
	}

	FileSystem* Context::fileSystem()
	{
		if(!hasInstance())
		{
			return nullptr;
		}
		return getInstance()->getApplication()->getFileSystem();
	}

	LibraryService* Context::libraryService()
	{
		if(!hasInstance())
		{
			return nullptr;
		}
		return getInstance()->getApplication()->getLibraryService();
	}

	Context::Context()
		:_members(new ContextPrivate())
	{

	}

	Context::~Context()
	{
		ContextPrivate* members = _members;
		_members = nullptr;
		delete _members;
	}

	Application *Context::getApplication()
	{
		ASSERT(isInitialized());
		return _members->application.get();
	}

	Console* Context::getConsole()
	{
		return _members->console.get();
	}

	Application *Context::getApplicationUnsafe()
	{
		return _members->application.get();
	}

	void Context::setApplication(std::unique_ptr<Application> application)
	{
		_members->application = std::move(application);
	}

	void Context::setConsole(std::unique_ptr<Console>&& console)
	{
		_members->console = std::move(console);
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
