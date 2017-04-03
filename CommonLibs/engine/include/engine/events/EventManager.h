#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	class EventSourceBase;
	class ISignalManager;

	/**
	* Event manager for the event of the application.
	* Every event source must be a member EventSourceId. Based on this id the sources are stored.
	* The EventSourceId not necessarly unique, the manager stores it in a vector.
	*/
	class EventManager 
		: private NonCopyable,
		  private NonMoveable
	{
	public:
		/**PIMPL */
		EventManager();
		
		/**PIMPL */
		virtual ~EventManager();

		/**Update the event sources*/
		void update();
		
		/**
		* Add a new event source. 
		* This event source lifetime will be managed by the manager
		* @param eventSource: Event source to store.
		*/
		void addEventSource(std::unique_ptr<EventSourceBase> &&eventSource);
		/**
		* Add a new event source.
		* This event source lifetime won't be managed by the manager the user must ensure that it won't die still it is registered.
		*/
		void registerEventSource(EventSourceBase*);
		/**Remove the given event source independently wether it was managed by the manager or not.*/
		void removeEventSource(const EventSourceBase*);

		/**Find the event source based on its EventSoruceId*/
		std::vector<EventSourceBase*> findEventSource(const std::string &key) const;
		
		/**Find the event source based on it's type*/
		template<class T_EventSource>
		std::vector<T_EventSource*> findEventSource() const;

		/**
		* The event manager has its own signal manager the handle signals. 
		* This signal manager is public accessable to publish a common signal manager to handle signals.
		* @return Signal manager of the event manager
		*/
		ISignalManager *getEventsSignalManager() const;
	protected:
		/**Collect all the event sources*/
		std::vector<EventSourceBase*> collectEventSources() const;

	private:
		/**Collect managed event source*/
		std::vector<EventSourceBase*> collectManagedEventSources() const;
		/**Collect unmanaged event source*/
		std::vector<EventSourceBase*> collectUnmanagedEventSources() const;
		/**
		* find a managed event source.
		* @param key: EventSourceId of the event source
		*/
		std::vector<EventSourceBase*> findManagedEventSource(const std::string &key) const;
		/**
		* find an unmanaged event source
		* @param key: EventSourceId of the event source
		*/
		std::vector<EventSourceBase*> findUnmanagedEventSource(const std::string &key) const;
		/**@return Returns overall event source count.*/
		uint32_t getNumOfEventSources() const;
		/**@return Returns the managed event source count.*/
		uint32_t getNumOfManagedEventSources() const;
		/**@return Returns the unmanaged event source count.*/
		uint32_t getNumOfUnmanagedEventSources() const;

	private:
		/**PIMPL*/
		struct EventManagerPrivate *_members = nullptr;
	};

	template<class T_EventSource>
	std::vector<T_EventSource*> EventManager::findEventSource() const
	{
		std::vector<T_EventSource*> result;
		std::vector<EventSourceBase*> founded = findEventSource(T_EventSource::EventSourceId);
		std::transform(founded.begin(), founded.end(), std::back_inserter(result),
					   [](EventSourceBase* source)->T_EventSource*{return static_cast<T_EventSource*>(source); });
		return result;
	}
}