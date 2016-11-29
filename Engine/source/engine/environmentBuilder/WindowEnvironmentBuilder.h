#pragma once

#include "engine/environmentBuilder/BaseBuilder.h"
namespace engine
{
	enum class ContextModuleType;
	namespace view
	{
		class WindowManager;
	}
	namespace environmentBuilder
	{
		class ApplicationBuilder;
		class BuildFinalizer;
	}
}


namespace engine
{
	namespace environmentBuilder
	{
		/**
		* This buildphase will initialize the window environment.
		*/
		class WindowEnvironmentBuilder : public BaseBuilder
		{
			friend class engine::environmentBuilder::ApplicationBuilder;
		private:
			/**
			* Initialize the window environment with the given module.
			* @param windowModule: Window handler module.
			*/
			WindowEnvironmentBuilder(const ContextModuleType windowModule);
		public:
			/**Destructor for PIMPL*/
			~WindowEnvironmentBuilder() ;

			/**Moveable*/
			WindowEnvironmentBuilder(WindowEnvironmentBuilder &&o);

			/**
			* Builds the window module.
			* @return Returns the next building phase.
			*/
			BuildFinalizer build();
		private:
			/** Create Glfw window and window manager.*/
			std::unique_ptr<view::WindowManager> createGlfwWindowManager();
			/** Create Sdl window and window manager.*/
			std::unique_ptr<view::WindowManager> createSdlWindowManager();
			/** Create Winapi window and window manager.*/
			std::unique_ptr<view::WindowManager> createWinApiWindowManager();

		private:
			/**PIMPL*/
			struct WindowEnvironmentBuilderPrivate *_members = nullptr;
		};
	}
}
