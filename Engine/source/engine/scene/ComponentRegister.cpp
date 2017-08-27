#include <stdafx.h>
#include <engine/scene/ComponentRegister.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/entityFramework/Entity.h>

#include <engine/render/Render.h>

namespace engine
{
	struct ComponentRegisterPrivate
	{
		Render* renderToRegister = nullptr;
	};

	ComponentRegister::ComponentRegister()
		: _members(new ComponentRegisterPrivate())
	{

	}

	ComponentRegister::~ComponentRegister()
	{
		delete _members;
		_members = nullptr;
	}

	void ComponentRegister::init(Render* render)
	{
		_members->renderToRegister = render;
	}

	void ComponentRegister::registerEntity(Entity* entity)
	{
		if(entity->hasCameraComponent())
		{
			_members->renderToRegister->addCamera(entity->getCameraComponent());
		}
		for(VisualComponent* component : entity->getVisualComponents())
		{
			registerVisualComponent(entity, component, _members->renderToRegister);
		}
	}
}