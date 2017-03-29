#pragma once

#include <engine/environmentBuilder/BaseBuilder.h>

namespace engine
{
	class WindowEnvironmentBuilder;
	class ContextBuilder;
	class EventSourceBase;
}

namespace engine
{
	class EventBuilder : public BaseBuilder
	{
		friend class ApplicationBuilder;
	public:
		enum class BasicInputType
		{
			Mouse,
			Keyboard
		};
	private:
		EventBuilder(const ContextModuleType windowModuleType);
	public:
		EventBuilder(EventBuilder &&eventBuilder);

		~EventBuilder();

		WindowEnvironmentBuilder build(const std::set<BasicInputType> &basicInputs);
		WindowEnvironmentBuilder skip();

	private:
		void initBasicInputs(const std::set<BasicInputType> &basicInputs) const;
		std::unique_ptr<EventManager> createEventManager();
		std::unique_ptr<EventSourceBase> createEventHandler(BasicInputType type) const;
		std::unique_ptr<EventSourceBase> createMouse() const;
		std::unique_ptr<EventSourceBase> createKeyboard() const;

	private:
		struct EventBuilderPrivate* _members = nullptr;
	};
}