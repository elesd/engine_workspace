#pragma once

namespace engine
{
	enum class BasicInputType;
	class EventManager;
	class EventSourceBase;

	/**
	* Each window has its own event manager and it has own inputs. In order to set up event sources like basic inputs
	* for each window, it is done once when the environment is built up.
	* This factory can create event manager for the newly created windows which supports the same input fields.
	* @note Later event manager's input can be changed in special cases.
	*/
	class EventManagerFactory
	{
		friend class EventBuilder;
	protected:
		/**
		* Creates the factory.
		* @param basicInputs: Inputs which are handled by default in EventManagers.
		*/
		EventManagerFactory(const std::set<BasicInputType> &basicInputs);
	public:
		/**PIMPL*/
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

		/**
		* @return Returns the modul specific implementation of the event manager.
		*/
		virtual std::unique_ptr<EventManager> createEventManagerImpl() = 0;
	private:
		/**PIMPL*/
		struct EventManagerFactoryPrivate *_members = nullptr;
	};
}
