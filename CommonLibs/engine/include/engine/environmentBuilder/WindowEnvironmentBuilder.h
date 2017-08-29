#pragma once

#include <engine/environmentBuilder/BaseBuilder.h>
namespace engine
{
	enum class ContextModuleType;
	class WindowManager;
	class EventBuilder;
	class BuildFinalizer;
	class GlobalResourceMapping;
	struct DeviceParameters;
}


namespace engine
{

	/**
	* This buildphase will initialize the window environment.
	*/
	class WindowEnvironmentBuilder : public BaseBuilder
	{
		friend class engine::EventBuilder;
	private:
		/**
		* Initialize the window environment with the given module.
		* @param windowModule: Window handler module.
		*/
		WindowEnvironmentBuilder(const ContextModuleType windowModule);
	public:
		/**Destructor for PIMPL*/
		~WindowEnvironmentBuilder();

		/**Moveable*/
		WindowEnvironmentBuilder(WindowEnvironmentBuilder &&o);

		/**
		* Builds the window module.
		* @return Returns the next building phase.
		*/
		BuildFinalizer build(const DeviceParameters& deviceParameters, const GlobalResourceMapping& resourceMapping);
	private:
		/** Create Glfw window and window manager.*/
		std::unique_ptr<WindowManager> createGlfwWindowManager(const DeviceParameters& deviceParameters, const GlobalResourceMapping& resourceMapping);
		/** Create Sdl window and window manager.*/
		std::unique_ptr<WindowManager> createSdlWindowManager(const DeviceParameters& deviceParameters, const GlobalResourceMapping& resourceMapping);
		/** Create Winapi window and window manager.*/
		std::unique_ptr<WindowManager> createWinApiWindowManager(const DeviceParameters& deviceParameters, const GlobalResourceMapping& resourceMapping);

	private:
		/**PIMPL*/
		struct WindowEnvironmentBuilderPrivate *_members = nullptr;
	};
}
