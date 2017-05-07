#include <stdafx.h>
#include <engine/events/Mouse.h>
//////////////////////////////////////////////////////////////////////////////

#include <engine/Context.h>
#include <engine/app/Application.h>
#include <engine/events/EventManager.h>

#include <engine/Types.h>

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
		ScreenSpacePosition position;
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

	MouseButtonState Mouse::getButtonState(MouseButton button) const
	{
		auto it = _members->buttonDescription.find(button);
		return it != _members->buttonDescription.end() ? it->second : MouseButtonState::Unknown;
	}

	void Mouse::onMouseMoved(int32_t x, int32_t y)
	{
		_members->position[0] = x;
		_members->position[1] = y;
	}

	ScreenSpacePosition Mouse::getPosition() const
	{
		return _members->position;
	}

	void Mouse::onLeftButtonPressed()
	{
		_members->buttonDescription[MouseButton::Left] = MouseButtonState::Pressed;
	}

	void Mouse::onRightButtonPressed()
	{
		_members->buttonDescription[MouseButton::Right] = MouseButtonState::Pressed;
	}

	void Mouse::onMiddleButtonPressed()
	{
		_members->buttonDescription[MouseButton::Middle] = MouseButtonState::Pressed;
	}

	void Mouse::onLeftButtonReleased()
	{
		_members->buttonDescription[MouseButton::Left] = MouseButtonState::Released;
	}

	void Mouse::onRightButtonReleased()
	{
		_members->buttonDescription[MouseButton::Right] = MouseButtonState::Released;
	}

	void Mouse::onMiddleButtonReleased()
	{
		_members->buttonDescription[MouseButton::Middle] = MouseButtonState::Released;
	}
}
