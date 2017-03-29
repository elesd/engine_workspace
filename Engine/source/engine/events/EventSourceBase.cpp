#include <stdafx.h>
#include <engine/events/EventSourceBase.h>
///////////////////////////////////////////////////////////////////////////////

namespace engine
{
	struct EventSourceBasePrivate
	{
		EventSourceBasePrivate(const std::string &id);

		const std::string id;
		bool enable = true;
	};
	EventSourceBasePrivate::EventSourceBasePrivate(const std::string &id)
		:id(id)
	{}


	EventSourceBase::EventSourceBase(const std::string &id)
		: _members(new EventSourceBasePrivate(id))
	{}

	EventSourceBase::~EventSourceBase()
	{
		delete _members;
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