#pragma once

#include <engine/constraints/NonCopyable.h>

namespace engine
{
	/**
	* Base class for event sources.
	*/
	class EventSourceBase
	{
	protected:
		/**
		* @param eventSourceId: id of the event source, not necessarly unique.
		*/
		EventSourceBase(const std::string &eventSourceId);
	public:
		/**PIMPL*/
		virtual ~EventSourceBase();

		EventSourceBase(const EventSourceBase&);

		EventSourceBase(EventSourceBase&&);

		EventSourceBase& operator=(const EventSourceBase&);

		EventSourceBase& operator=(EventSourceBase&&);

		/** Setter for enable property.	*/
		void setEventsEnabled(bool);
		/** @return Returns true if the event source is enabled.*/
		bool isEventsEnabled() const;
		/** @return Returns the event source id.*/
		const std::string &getEventSourceId() const;

	private:
		/**PIMPL*/
		struct EventSourceBasePrivate *_members;
	};
}