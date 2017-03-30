#pragma once
#include <engine/app/IMain.h>
#include <engine/signalSlot/SlotHolder.h>

namespace engine
{
	enum class KeyboardButton;
}

class TestMain : public engine::IMain,
	public engine::SlotHolder
{
public:
	void load();

	void update();

	void render();

	void onMouseMoved(int x, int y);
	void onMouseWheel(int x, int y, int w);

	void onMouseLeftDown(int x, int y);
	void onMouseRightDown(int x, int y);
	void onMouseMiddleDown(int x, int y);
	void onMouseLeftUp(int x, int y);
	void onMouseRightUp(int x, int y);
	void onMouseMiddleUp(int x, int y);
	void onKeyPressed(engine::KeyboardButton button);
	void onKeyReleased(engine::KeyboardButton button);

	engine::ISignalManager* getSignalManager() const override;
};