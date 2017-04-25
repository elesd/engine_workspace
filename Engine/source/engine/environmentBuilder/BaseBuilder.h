#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/Context.h>


namespace engine
{
	class Application;
	class WindowManager;
	class EventManager;
	class EventBuilder;
	enum class ContextModuleType;
	/**
	* Base class for builder phases.
	* Only via this class one can set up context parameters.
	*/
	class BaseBuilder : NonCopyable
	{
	protected:
		/**Default constructor*/
		BaseBuilder() = default;
		/**Default destructor*/
		virtual ~BaseBuilder() {}

		/**
		* Add a module type which is initialized during build phase
		* @param value: Module which is initialized successfully
		*/
		void addModule(const ContextModuleType value);

		/**
		* Set the context application.
		* @param app: Application to use
		*/
		void setApplication(std::unique_ptr<Application> app);

		void setEventBuilder(Application *app, std::unique_ptr<EventBuilder> &&eventBuilder);

		/**
		* Set the window manager of the context.
		* @param manager: window manager to use
		*/
		void setWindowManager(std::unique_ptr<WindowManager> manager);

		/**
		* When the environment is built up this function finalize the context.
		*/
		void setInitialized();
	};
}
