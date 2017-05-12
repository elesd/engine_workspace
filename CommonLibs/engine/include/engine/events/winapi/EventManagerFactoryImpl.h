#pragma once

#include <engine/events/EventManagerFactory.h>

namespace engine
{
	namespace winapi
	{
		/**Winapi specific event manager factory.*/
		class EventManagerFactoryImpl : public EventManagerFactory
		{
			friend class EventBuilder;
			/**@copydoc EventManagerFactory::EventManagerFactory*/
			EventManagerFactoryImpl(const std::set<BasicInputType> &basicInputs);
		private:
			/**@return Returns the winapi mouse.*/
			std::unique_ptr<EventSourceBase> createMouse() const override;
			/**@return Returns the winapi keyboard.*/
			std::unique_ptr<EventSourceBase> createKeyboard() const override;
			/**@return Returns the winapi event manager.*/
			std::unique_ptr<EventManager> createEventManagerImpl() override;
		};
	}
}
