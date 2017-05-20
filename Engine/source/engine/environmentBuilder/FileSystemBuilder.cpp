#include <stdafx.h>
#include <engine/environmentBuilder/FileSystemBuilder.h>

#include <engine/environmentBuilder/EventBuilder.h>

#include <engine/fileSystem/FileSystem.h>
namespace engine
{
	struct FileSystemBuilderPrivate
	{
		Application *app = nullptr;
		ContextModuleType windowModule;
		FileSystemBuilderPrivate(Application *app, const ContextModuleType windowModule) 
			: app(app)
			, windowModule(windowModule) 
		{ }
	};

	FileSystemBuilder::FileSystemBuilder(Application *app, const ContextModuleType windowModule)
		: _members(new FileSystemBuilderPrivate(app, windowModule))
	{
		
	}

	FileSystemBuilder::FileSystemBuilder(FileSystemBuilder &&o)
		: _members(o._members)
	{
		o._members = nullptr;
	}

	FileSystemBuilder::~FileSystemBuilder()
	{
		delete _members;
		_members = nullptr;
	}

	EventBuilder FileSystemBuilder::build(const FileSystemSettings &settings)
	{
		{
			std::unique_ptr<FileSystem> fileSystem(new FileSystem(settings));
			setFileSystem(_members->app, std::move(fileSystem));
		}
		EventBuilder result(_members->windowModule, _members->app);
		return result;
	}
}