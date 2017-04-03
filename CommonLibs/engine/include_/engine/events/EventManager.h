#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	class EventSourceBase;
	class ISignalManager;

	class EventManager 
		: private NonCopyable,
		  private NonMoveable
	{
	public:
		EventManager();
		virtual ~EventManager();

		void update();
		
		void addEventSource(std::unique_ptr<EventSourceBase> &&eventSource);
		void registerEventSource(EventSourceBase*);
		void removeEventSource(const EventSourceBase*);
		std::vector<EventSourceBase*> findEventSource(const std::string &key) const;
		
		template<class T_EventSource>
		std::vector<T_EventSource*> findEventSource() const;
		ISignalManager *getEventsSignalManager() const;
	protected:
		std::vector<EventSourceBase*> collectEventSources() const;

	private:
		std::vector<EventSourceBase*> collectManagedEventSources() const;
		std::vector<EventSourceBase*> collectUnmanagedEventSources() const;
		std::vector<EventSourceBase*> findManagedEventSource(const std::string &key) const;
		std::vector<EventSourceBase*> findUnmanagedEventSource(const std::string &key) const;
		uint32_t getNumOfEventSources() const;
		uint32_t getNumOfManagedEventSources() const;
		uint32_t getNumOfUnmanagedEventSources() const;

	private:
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