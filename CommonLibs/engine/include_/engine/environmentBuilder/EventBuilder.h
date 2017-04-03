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
	Class for building the event system.
	*/
	class EventBuilder : public BaseBuilder
	{
		friend class ApplicationBuilder;
	public:
		/** Basic input types of the engine */
		enum class BasicInputType
		{
			Mouse, /**< Mouse input*/
			Keyboard /**< Keyboard input*/
		};
	private:
		/**
		Creates the builder
		@param windowModuleType: The type of the window module.
		*/
		EventBuilder(const ContextModuleType windowModuleType);
	public:
		/** Move for PIMPL	*/
		EventBuilder(EventBuilder &&);

		/** PIMPL*/
		~EventBuilder();

		/**
		Builds the event manager.
		@param basicInputs: These inputs will be handled from the beginning of the engine initialization.
		@return Returns the next build step. 
		*/
		WindowEnvironmentBuilder build(const std::set<BasicInputType> &basicInputs);
		/**
		The event system is not necessary for the engine, it can be skipped, but in this case no events are supported.
		@return Returns the next build step.
		*/
		WindowEnvironmentBuilder skip();

	private:
		/**
		Initialize the basic inputs.
		*/
		void initBasicInputs(const std::set<BasicInputType> &) const;
		/**
		Creates the event manager
		@return Returns the created event manager
		*/
		std::unique_ptr<EventManager> createEventManager();
		/**
		Creates the event handler for the input type.
		@param type: Type of the input.
		@return Returns the event handler.
		*/
		std::unique_ptr<EventSourceBase> createEventHandler(BasicInputType type) const;
		/**
		Creates the mouse event handler.
		@return Returns a mouse implementation based on the window module type
		*/
		std::unique_ptr<EventSourceBase> createMouse() const;
		/**
		Creates the keyboard event handler.
		@return Returns a keyboard implementation based on the window module type
		*/
		std::unique_ptr<EventSourceBase> createKeyboard() const;

	private:
		/**PIMPL*/
		struct EventBuilderPrivate* _members = nullptr;
	};
}