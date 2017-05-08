#pragma once

#include <engine/environmentBuilder/BaseBuilder.h>


namespace engine
{
	class WindowEnvironmentBuilder;
	class ContextBuilder;
	class EventSourceBase;
	class Application;
	/**
	* Input event source types
	*/
	enum class BasicInputType
	{
		Mouse,
		Keyboard
	};

	/**
	* Build step for EventManager of the application
	*/
	class EventBuilder : public BaseBuilder
	{
		friend class ApplicationBuilder;
	public:
	private:
		/**
		* Construct a builder. It can be done only another builder step, therefore it is private.
		* @param windowModuleType: Type of the window moudle.
		*/
		EventBuilder(const ContextModuleType windowModuleType, Application *application);
	public:
		/**PIMPL*/
		EventBuilder(EventBuilder &&eventBuilder);

		/**PIMPL*/
		~EventBuilder() override;

		/**
		* Initialize the event environment and creates the next build step
		* @param basicInputs: Basic input sources. Later can be extended via EventManager.
		* @see EventManager
		*/
		WindowEnvironmentBuilder build(const std::set<BasicInputType> &basicInputs);
		/**
		* It is not a mandatory step, the application can work without events.
		*/
		WindowEnvironmentBuilder skip();

	private:
		/**PIMPL*/
		struct EventBuilderPrivate* _members = nullptr;
	};
}
