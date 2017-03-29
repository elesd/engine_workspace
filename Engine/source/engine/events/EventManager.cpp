#include <stdafx.h>
#include <engine/events/EventManager.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/events/EventSourceBase.h>
#include <engine/signalSlot/SignalManager.h>

namespace engine
{
	struct EventManagerPrivate
	{
		std::map<std::string, std::vector<std::unique_ptr<EventSourceBase>>> managedEventSources;
		std::map<std::string, std::vector<EventSourceBase*>> unmanagedEventSources;
		ISignalManager *eventsSignalManager = nullptr;
		EventManagerPrivate();
		~EventManagerPrivate();
	};

	EventManagerPrivate::EventManagerPrivate()
	{
		eventsSignalManager = new SignalManager();
	}

	EventManagerPrivate::~EventManagerPrivate()
	{
		delete eventsSignalManager;
	}

	EventManager::EventManager()
		: _members(new EventManagerPrivate())
	{}

	EventManager::~EventManager()
	{
		delete _members;
	}

	void EventManager::update()
	{
		_members->eventsSignalManager->update();
	}

	void EventManager::addEventSource(std::unique_ptr<EventSourceBase> &&eventSource)
	{
		_members->managedEventSources[eventSource->getEventSourceId()].emplace_back(std::move(eventSource));
	}

	void EventManager::registerEventSource(EventSourceBase *eventSource)
	{
		_members->unmanagedEventSources[eventSource->getEventSourceId()].push_back(eventSource);
	}

	void EventManager::removeEventSource(const EventSourceBase* source)
	{
		std::string keyToDelete = "";
		bool deleteKey = false;
		for(auto &pair : _members->managedEventSources)
		{
			auto it = std::remove_if(pair.second.begin(), pair.second.end(),
									 [source](const std::unique_ptr<EventSourceBase> &s)->bool{return s.get() == source; });
			pair.second.erase(it, pair.second.end());
			if(pair.second.empty())
			{
				keyToDelete = pair.first;
				deleteKey = true;
			}
		}
		if(deleteKey)
		{
			_members->managedEventSources.erase(keyToDelete);
			deleteKey = false;
		}
		for(auto &pair : _members->unmanagedEventSources)
		{
			auto it = std::remove_if(pair.second.begin(), pair.second.end(),
									 [source](EventSourceBase* s)->bool{return s == source; });
			pair.second.erase(it, pair.second.end());
			if(pair.second.empty())
			{
				keyToDelete = pair.first;
				deleteKey = true;
			}
		}
		if(deleteKey)
		{
			_members->unmanagedEventSources.erase(keyToDelete);
			deleteKey = false;
		}
	}

	std::vector<EventSourceBase*> EventManager::findEventSource(const std::string &key) const
	{
		std::vector<EventSourceBase*> result = findUnmanagedEventSource(key);
		std::vector<EventSourceBase*> managedEventSources = findManagedEventSource(key);
		if(!managedEventSources.empty())
		{
			result.reserve(result.size() + managedEventSources.size());
			std::copy(managedEventSources.begin(), managedEventSources.end(), std::back_inserter(result));
		}
		return result;
	}


	std::vector<EventSourceBase*> EventManager::findManagedEventSource(const std::string &key) const
	{
		auto it = _members->managedEventSources.find(key);
		if(it == _members->managedEventSources.end())
			return {};
		
		std::vector<EventSourceBase*> result;
		result.reserve(it->second.size());
		std::transform(it->second.begin(), it->second.end(), std::back_inserter(result),
					   [](const std::unique_ptr<EventSourceBase> &source)->EventSourceBase*{return source.get(); });
		return result;
	}

	std::vector<EventSourceBase*> EventManager::findUnmanagedEventSource(const std::string &key) const
	{
		auto it = _members->unmanagedEventSources.find(key);
		return it == _members->unmanagedEventSources.end() ? std::vector<EventSourceBase*>() : it->second;
	}
	
	std::vector<EventSourceBase*> EventManager::collectEventSources() const
	{
		std::vector<EventSourceBase*> result = collectManagedEventSources();
		std::vector<EventSourceBase*> unmanagedEventSources = collectUnmanagedEventSources();
		if(!unmanagedEventSources.empty())
		{
			result.reserve(result.size() + unmanagedEventSources.size());
			std::copy(unmanagedEventSources.begin(), unmanagedEventSources.end(), std::back_inserter(result));
		}
		return result;
	}
	
	std::vector<EventSourceBase*> EventManager::collectManagedEventSources() const
	{
		std::vector<EventSourceBase*> result;
		result.reserve(getNumOfManagedEventSources());
		for(auto &pair : _members->managedEventSources)
		{
			std::transform(pair.second.begin(), pair.second.end(), std::back_inserter(result),
						   [](const std::unique_ptr<EventSourceBase> &source)->EventSourceBase*{return source.get(); });
		}
		return result;
	}

	std::vector<EventSourceBase*> EventManager::collectUnmanagedEventSources() const
	{
		std::vector<EventSourceBase*> result;
		result.reserve(getNumOfUnmanagedEventSources());
		for(auto pair : _members->unmanagedEventSources)
		{
			std::copy(pair.second.begin(), pair.second.end(), std::back_inserter(result));
		}
		return result;
	}

	uint32_t EventManager::getNumOfEventSources() const
	{
		return getNumOfManagedEventSources() + getNumOfUnmanagedEventSources();
	}

	uint32_t EventManager::getNumOfManagedEventSources() const
	{
		uint32_t count = 0;
		for(auto &pair : _members->managedEventSources)
		{
			count += pair.second.size();
		}
		return count;
	}

	uint32_t EventManager::getNumOfUnmanagedEventSources() const
	{
		uint32_t count = 0;
		for(auto pair : _members->unmanagedEventSources)
		{
			count += pair.second.size();
		}
		return count;
	}

	ISignalManager *EventManager::getEventsSignalManager() const
	{
		return _members->eventsSignalManager;
	}
}