#pragma once
#include <engine/app/GameMain.h>
#include <engine/constraints/NonMoveable.h>
#include <engine/signalSlot/SlotHolder.h>

namespace engine
{
	class StateBase;
	enum class KeyboardButton;
}

class Tutorial
	: public engine::GameMain

{
public:
	Tutorial() = default;
	~Tutorial() override {};

private:
	void updateGame() override;
	WindowCreationParameter getWindowCreationParameters() override;
	std::unique_ptr<engine::StateBase> createStartState(engine::Window* mainWindow) override;
};
