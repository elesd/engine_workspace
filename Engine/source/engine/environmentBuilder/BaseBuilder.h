#pragma once

#include "engine/constraints/NonCopyable.h"
#include "engine/Context.h"

namespace engine
{
	namespace app
	{
		class Application;
	}
	namespace view
	{
		class WindowManager;
	}
	enum class ContextModuleType;
}

namespace engine
{

	namespace environmentBuilder
	{
		/**
		* Base class for builder phases.
		* Only via this class one can set up context parameters.
		*/
		class BaseBuilder : constraints::NonCopyable
		{
		protected:
			/**Default constructor*/
			BaseBuilder() = default;
			/**Default destructor*/
			~BaseBuilder() override {}

			/**
			* Add a module type which is initialized during build phase
			* @param value: Module which is initialized successfully
			*/
			void addModule(const ContextModuleType value);

			/**
			* Set the context application.
			* @param app: Application to use
			*/
			void setApplication(std::unique_ptr<app::Application> app);

			/**
			* Set the window manager of the context.
			* @param manager: window manager to use
			*/
			void setWindowManager(std::unique_ptr<view::WindowManager> manager);

			/**
			* When the environment is built up this function finalize the context.
			*/
			void setInitialized();
		};
	}
}
