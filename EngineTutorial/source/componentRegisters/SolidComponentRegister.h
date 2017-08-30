#pragma once

#include <engine/scene/ComponentRegister.h>

class SolidComponentRegister
	: public engine::ComponentRegister
{
public:
	SolidComponentRegister()
	{	};
	~SolidComponentRegister() override {};
private:
	void registerVisualComponent(engine::Entity* entity, engine::VisualComponent* visualComponent, engine::Render* renerer);

};