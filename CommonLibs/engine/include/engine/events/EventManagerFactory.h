#pragma once

namespace engine
{
	enum class BasicInputType;
	class EventManager;
	class EventSourceBase;

	class EventManagerFactory
	{
		friend class EventBuilder;
	protected:
		EventManagerFactory(const std::set<BasicInputType> &basicInputs);
	public:
		virtual ~EventManagerFactory();
		/** @return Returns the created event manager which is belong to the window module type*/
		std::unique_ptr<EventManager> createEventManager();
	private:
		/**
		* Initialization of basic input types
		* @param basicInputs: basic input types
		*/
		void initBasicInputs(EventManager *eventManager, const std::set<BasicInputType> &basicInputs) const;
		/**
		* @param type: Source type
		* @return Returns the created event source which is belong to the given type
		*/
		std::unique_ptr<EventSourceBase> createEventHandler(BasicInputType type) const;
		/**
		* @return Returns a mouse event source based on the window module type
		*/
		virtual std::unique_ptr<EventSourceBase> createMouse() const = 0;
		/**
		* @return Returns a keyboardevent source based on the window module type
		*/
		virtual std::unique_ptr<EventSourceBase> createKeyboard() const = 0;

		virtual std::unique_ptr<EventManager> createEventManagerImpl() = 0;
	private:
		struct EventManagerFactoryPrivate *_members = nullptr;
	};
}
