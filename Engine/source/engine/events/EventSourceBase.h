#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/PIMPLCopyable.h>
#include <engine/constraints/PIMPLMoveable.h>

namespace engine
{
	/**
	* Base class for event sources.
	*/
	class EventSourceBase : public PIMPLCopyable<EventSourceBase>
		, public PIMPLMoveable<EventSourceBase>
	{
	protected:
		/**
		* @param eventSourceId: id of the event source, not necessarly unique.
		*/
		EventSourceBase(const std::string &eventSourceId);
	public:
		/**PIMPL*/
		virtual ~EventSourceBase();

	public:

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