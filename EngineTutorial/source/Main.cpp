#include "stdafx.h"

#include <engine/app/Application.h>
#include <engine/environmentBuilder/EventBuilder.h>
#include <engine/environmentBuilder/EasyBuilder.h>
#include <engine/fileSystem/FileSystem.h>
#include <engine/ModuleDefinitions.h>

#include <engine/render/GlobalResourceMapping.h>

#include <engine/view/Console.h>

#include <engine/video/Driver.h>

#include <Tutorial.h>

namespace
{
#if TUTORIAL_USE_GLFW
	engine::ContextModuleType windowModule = engine::ContextModuleType::Glfw;
#else
	engine::ContextModuleType windowModule = engine::ContextModuleType::Sdl;
#endif
	///////////////////////////////////////////////////////////////////////////////////
#if TUTORIAL_USE_OPENGL
	void setupOpengl(engine::EasyBuilder& builder)
	{
		engine::DeviceParameters deviceParameters;
		deviceParameters.version = engine::DriverVersion::OpenGL_Core_3_3;
		builder.setDeviceParameters(deviceParameters);
	}
#else
	void setupDirectX(engine::EasyBuilder& builder)
	{
		engine::DeviceParameters deviceParameter;
		deviceParameter.version = engine::DriverVersion::DirectX11;
		builder.setDeviceParameters(deviceParameter);
	}
#endif
	void setupCommonSetting(engine::EasyBuilder& builder)
	{
		builder.AddInput(engine::BasicInputType::Keyboard)
			.AddInput(engine::BasicInputType::Mouse);
		engine::FileSystemSettings settings;
		settings.workingDirectory = "..\\data\\";
		builder.setFileSystemSetting(settings);
		std::map<engine::GlobalResource, std::string> shaderResources =
		{
			std::make_pair(engine::GlobalResource::WorldMatrix, "WorldMatrix"),
			std::make_pair(engine::GlobalResource::InvWorldMatrix, "InvWorldMatrix"),
			std::make_pair(engine::GlobalResource::ViewMatrix, "ViewMatrix"),
			std::make_pair(engine::GlobalResource::ViewWorldMatrix, "ViewWorldMatrix"),
			std::make_pair(engine::GlobalResource::InvViewMatrix, "InvViewMatrix"),
			std::make_pair(engine::GlobalResource::InvViewWorldMatrix, "InvViewWorldMatrix"),
			std::make_pair(engine::GlobalResource::ProjectionViewMatrix, "ProjectionViewMatrix"),
			std::make_pair(engine::GlobalResource::InvProjectionViewMatrix,"InvProjectionViewMatrix"),
			std::make_pair(engine::GlobalResource::ProjectionMatrix, "ProjectionMatrix"),
			std::make_pair(engine::GlobalResource::InvProjectionMatrix,"InvProjectionMatrix"),
			std::make_pair(engine::GlobalResource::ProjectionViewWorldMatrix,"ProjectionViewWorldMatrix"),
			std::make_pair(engine::GlobalResource::InvProjectionViewWorldMatrix,"InvProjectionViewWorldMatrix"),
			std::make_pair(engine::GlobalResource::CameraPosition,"CameraPosition")
		};
		engine::GlobalResourceMapping resourceMapping(shaderResources);
		builder.setGlobalResourceMapping(resourceMapping);
	}
}

#if TUTORIAL_USE_WINAPI == 0

int main(int argc, char* argv[])
{
	std::unique_ptr<engine::GameMain> main(new Tutorial());
	engine::EasyBuilder builder(std::move(main), windowModule);
	setupCommonSetting(builder);
	setupOpengl(builder);
	engine::Application *app = builder.buildEngine(argc, argv);
	engine::Context::console()->print("Application starts");
	app->run();
	return 0;
}
#else

int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,
				   int nCmdShow)
{
	std::unique_ptr<engine::GameMain> main(new Tutorial());
	engine::EasyBuilder builder(std::move(main), engine::ContextModuleType::WinApi);
	setupCommonSetting(builder);
	engine::Application *app = builder.buildEngine(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	engine::Context::console()->print("Application starts");
	app->run();

	return 0;
}

#endif


