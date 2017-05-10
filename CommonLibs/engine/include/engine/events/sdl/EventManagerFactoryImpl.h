#pragma once

#include <engine/events/EventManagerFactory.h>

namespace engine
{
	namespace sdl
	{
		class EventManagerFactoryImpl : public EventManagerFactory
		{
			friend class EventBuilder;
			EventManagerFactoryImpl(const std::set<BasicInputType> &basicInputs);
		private:

			std::unique_ptr<EventSourceBase> createMouse() const override;
			std::unique_ptr<EventSourceBase> createKeyboard() const override;
			std::unique_ptr<EventManager> createEventManagerImpl() override;
		};
	}
}
