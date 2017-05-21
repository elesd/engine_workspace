#include <stdafx.h>
#include <engine/events/EventSourceBase.h>
///////////////////////////////////////////////////////////////////////////////

namespace engine
{
	struct EventSourceBasePrivate
	{
		EventSourceBasePrivate(const std::string &id);
		EventSourceBasePrivate(const EventSourceBasePrivate& o)
			: id(o.id)
			, enable(o.enable)
		{
		}
		const std::string id;
		bool enable = true;
	};
	EventSourceBasePrivate::EventSourceBasePrivate(const std::string &id)
		:id(id)
	{
	}


	EventSourceBase::EventSourceBase(const std::string &id)
		: _members(new EventSourceBasePrivate(id))
	{
	}

	EventSourceBase::~EventSourceBase()
	{
		delete _members;
	}

	EventSourceBase::EventSourceBase(const EventSourceBase& o)
		: _members(o._members ? new EventSourceBasePrivate(*o._members) : nullptr)
	{

	}

	EventSourceBase::EventSourceBase(EventSourceBase&& o)
		: _members(o._members)
	{
		o._members = nullptr;
	}

	EventSourceBase& EventSourceBase::operator=(const EventSourceBase& o)
	{
		delete _members;
		_members = o._members ? new EventSourceBasePrivate(*o._members) : nullptr;
		return *this;
	}

	EventSourceBase& EventSourceBase::operator=(EventSourceBase&& o)
	{
		delete _members;
		_members = o._members;
		o._members = nullptr;
		return *this;
	}

	void EventSourceBase::setEventsEnabled(bool v)
	{
		_members->enable = v;
	}

	bool EventSourceBase::isEventsEnabled() const
	{
		return _members->enable;
	}

	const std::string &EventSourceBase::getEventSourceId() const
	{
		return _members->id;
	}
}