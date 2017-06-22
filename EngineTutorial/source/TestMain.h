#pragma once
#include <engine/app/IMain.h>
#include <engine/constraints/NonMoveable.h>
#include <engine/signalSlot/SlotHolder.h>

namespace engine
{
	class StateBase;
	enum class KeyboardButton;
}

class TestMain 
	: public engine::IMain
	, public engine::SlotHolder
	, private engine::NonMoveable

{
public:
	TestMain();
	~TestMain() override;

	void load();

	void update();

	void render();

	engine::ISignalManager* getSignalManager() const override;

	void setStartState(std::unique_ptr<engine::StateBase> &&);
private:
	struct TestMainPrivate* _members = nullptr;
};
