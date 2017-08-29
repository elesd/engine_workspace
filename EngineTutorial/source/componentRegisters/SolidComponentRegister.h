#pragma once

#include <engine/scene/ComponentRegister.h>

class SolidComponentRegister
	: public engine::ComponentRegister
{
public:
	SolidComponentRegister(uint32_t tutorialId)
		: _tutorialId(tutorialId)
	{	};
	~SolidComponentRegister() override {};
private:
	void registerVisualComponent(engine::Entity* entity, engine::VisualComponent* visualComponent, engine::Render* renerer);

private:
	uint32_t _tutorialId = 0;
};