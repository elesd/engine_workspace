#pragma once

#include <engine/events/EventContainer.h>
#include <engine/events/EventSourceBase.h>

namespace engine
{
	class EventHandler :
		public EventSourceBase,
		private EventContainer
	{
	protected:
		EventHandler(const std::string &eventSourceId);
	public:
		~EventHandler() override;
	protected:
		using EventContainer::storeEvent;
	private:
		void updateEventsImpl() override;
	};

}