#pragma once

#include <engine/environmentBuilder/BaseBuilder.h>

namespace engine
{
	class WindowEnvironmentBuilder;
	class ContextBuilder;
	class EventSourceBase;
}

namespace engine
{
	/**
	* Build step for EventManager of the application
	*/
	class EventBuilder : public BaseBuilder
	{
		friend class ApplicationBuilder;
	public:
		/**
		* Input event source types
		*/
		enum class BasicInputType
		{
			Mouse,
			Keyboard
		};
	private:
		/**
		* Construct a builder. It can be done only another builder step, therefore it is private.
		* @param windowModuleType: Type of the window moudle.
		*/
		EventBuilder(const ContextModuleType windowModuleType);
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
		/**
		* Initialization of basic input types
		* @param basicInputs: basic input types
		*/
		void initBasicInputs(const std::set<BasicInputType> &basicInputs) const;
		/** @return Returns the created event manager which is belong to the window module type*/
		std::unique_ptr<EventManager> createEventManager();
		/** 
		* @param type: Source type
		* @return Returns the created event source which is belong to the given type
		*/
		std::unique_ptr<EventSourceBase> createEventHandler(BasicInputType type) const;
		/**
		* @return Returns a mouse event source based on the window module type
		*/
		std::unique_ptr<EventSourceBase> createMouse() const;
		/**
		* @return Returns a keyboardevent source based on the window module type
		*/
		std::unique_ptr<EventSourceBase> createKeyboard() const;

	private:
		/**PIMPL*/
		struct EventBuilderPrivate* _members = nullptr;
	};
}