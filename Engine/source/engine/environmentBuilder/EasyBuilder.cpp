#include <stdafx.h>
#include <engine/environmentBuilder/EasyBuilder.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/app/winapi/WinApiApplicationParameter.h>
#include <engine/app/IMain.h>
#include <engine/environmentBuilder/ApplicationBuilder.h>
#include <engine/environmentBuilder/BuildFinalizer.h>
#include <engine/environmentBuilder/ContextBuilder.h>
#include <engine/environmentBuilder/EventBuilder.h>
#include <engine/environmentBuilder/FileSystemBuilder.h>
#include <engine/environmentBuilder/WindowEnvironmentBuilder.h>

#include <engine/fileSystem/FileSystem.h>

#include <engine/ModuleDefinitions.h>

#include <engine/render/GlobalResourceMapping.h>
#include <engine/video/Driver.h>

namespace engine
{
	struct EasyBuilderPrivate
	{
		std::unique_ptr<IMain> main;
		std::set<engine::BasicInputType> inputs;
		FileSystemSettings fileSystemSettings;
		engine::ContextModuleType windowModule;
		DeviceParameters deviceParameters;
		GlobalResourceMapping resourceMapping;
	};

	EasyBuilder::EasyBuilder(std::unique_ptr<IMain> &&main, engine::ContextModuleType windowModul)
		:_members(new EasyBuilderPrivate())
	{
		_members->main = std::move(main);
		_members->windowModule = windowModul;
		_members->fileSystemSettings.workingDirectory = "./";
	}

	EasyBuilder::~EasyBuilder()
	{
		delete _members;
	}

	EasyBuilder& EasyBuilder::AddInput(engine::BasicInputType input)
	{
		_members->inputs.insert(input);
		return *this;
	}

	void EasyBuilder::setFileSystemSetting(const FileSystemSettings &settings)
	{
		_members->fileSystemSettings = settings;
	}

	void EasyBuilder::setDeviceParameters(const DeviceParameters& deviceParameters)
	{
		_members->deviceParameters = deviceParameters;
	}

	void EasyBuilder::setGlobalResourceMapping(const GlobalResourceMapping& resourceMapping)
	{

	}

	Application* EasyBuilder::buildEngine(HINSTANCE hInstance,
								  HINSTANCE hPrevInstance,
								  LPSTR lpCmdLine,
								  int nCmdShow) const
	{
		ASSERT(_members->windowModule == ContextModuleType::WinApi);
		std::unique_ptr<IApplicationParameter> args(new winapi::WinApiApplicationParameter(hInstance, hPrevInstance, lpCmdLine, nCmdShow));
		buildEngine(std::move(args));
		return Context::getInstance()->getApplication();
	}

	Application* EasyBuilder::buildEngine(int argc, char* argv[]) const
	{
		ASSERT(_members->windowModule == ContextModuleType::Sdl
		|| _members->windowModule == ContextModuleType::Glfw);
		std::unique_ptr<IApplicationParameter> args(new StandardApplicationParameter(argc, argv));
		buildEngine(std::move(args));
		return Context::getInstance()->getApplication();
	}

	void EasyBuilder::buildEngine(std::unique_ptr<IApplicationParameter> args) const
	{
		ContextBuilder envBuilder({_members->windowModule});
		ApplicationBuilder appBuilder = envBuilder.buildForApplication();
		FileSystemBuilder fsBuilder = appBuilder.build(std::move(args), std::move(_members->main));
		EventBuilder eventBuilder = fsBuilder.build(_members->fileSystemSettings);
		WindowEnvironmentBuilder windowBuilder = eventBuilder.build(_members->inputs);
		BuildFinalizer lastStep = windowBuilder.build(_members->deviceParameters, _members->resourceMapping);
		lastStep.build();
	}

}
