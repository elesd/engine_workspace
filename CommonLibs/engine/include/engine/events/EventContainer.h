#pragma once


namespace engine
{
	class EventContainer
	{
	public:
		EventContainer();
		~EventContainer();
		EventContainer(const EventContainer &o);
		EventContainer(EventContainer &&o);

		EventContainer& operator=(const EventContainer &o);
		EventContainer& operator=(EventContainer &&o);
	protected:
		void storeEvent(std::function<void()> &&event);
		std::vector<std::function<void()>> clearEvents();
		bool hasStoredEvents() const;
	private:
		struct EventContainerPrivate *_members = nullptr;
	};
}

