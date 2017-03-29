#include <stdafx.h>
#include <engine/events/Mouse.h>
//////////////////////////////////////////////////////////////////////////////

#include <engine/Context.h>
#include <engine/app/Application.h>
#include <engine/events/EventManager.h>

namespace
{
	engine::MouseButtonState getDescriptionValue(const std::map<engine::MouseButton, engine::MouseButtonState> &info, engine::MouseButton button)
	{
		auto it = info.find(button);
		return it == info.end() ? engine::MouseButtonState::Unknown : it->second;
	}
}

namespace engine
{
	const std::string Mouse::EventSourceId = "Mouse";

	struct MousePrivate
	{
		std::map<MouseButton, MouseButtonState> buttonDescription;
	};

	Mouse::Mouse()
		:EventSourceBase(EventSourceId),
		_members(new MousePrivate())
	{
	}

	Mouse::~Mouse()
	{
		delete _members;
		_members = nullptr;
	}

	ISignalManager *Mouse::getSignalManager() const
	{
		return Context::getInstance()->getApplication()->getEventManager()->getEventsSignalManager();
	}

	MouseButtonState Mouse::getButtonState(MouseButton button) const
	{
		auto it = _members->buttonDescription.find(button);
		return it != _members->buttonDescription.end() ? it->second : MouseButtonState::Unknown;
	}

	void Mouse::onLeftButtonPressed(const int32_t x, const int32_t y)
	{
		_members->buttonDescription[MouseButton::Left] = MouseButtonState::Pressed;
	}

	void Mouse::onRightButtonPressed(const int32_t x, const int32_t y)
	{
		_members->buttonDescription[MouseButton::Right] = MouseButtonState::Pressed;
	}

	void Mouse::onMiddleButtonPressed(const int32_t x, const int32_t y)
	{
		_members->buttonDescription[MouseButton::Middle] = MouseButtonState::Pressed;
	}

	void Mouse::onLeftButtonReleased(const int32_t x, const int32_t y)
	{
		_members->buttonDescription[MouseButton::Left] = MouseButtonState::Released;
	}

	void Mouse::onRightButtonReleased(const int32_t x, const int32_t y)
	{
		_members->buttonDescription[MouseButton::Right] = MouseButtonState::Released;
	}

	void Mouse::onMiddleButtonReleased(const int32_t x, const int32_t y)
	{
		_members->buttonDescription[MouseButton::Middle] = MouseButtonState::Released;
	}
}