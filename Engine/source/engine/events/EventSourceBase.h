#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/PIMPLCopyable.h>
#include <engine/constraints/PIMPLMoveable.h>

namespace engine
{
	class EventSourceBase : public PIMPLCopyable<EventSourceBase>
		, public PIMPLMoveable<EventSourceBase>
	{
	protected:
		EventSourceBase(const std::string &eventSourceId);
	public:
		//EventSourceBase(EventSourceBase &&o);
		//EventSourceBase(const EventSourceBase &o);
		virtual ~EventSourceBase();
		//EventSourceBase &operator=(EventSourceBase &&o);
		//EventSourceBase &operator=(const EventSourceBase &o);

	public:

		void setEventsEnabled(bool v);
		bool isEventsEnabled() const;
		const std::string &getEventSourceId() const;

	private:
		struct EventSourceBasePrivate *_members;
	};
}