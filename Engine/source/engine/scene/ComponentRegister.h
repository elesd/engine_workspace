#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	class CameraComponent;
	class Component;
	class Entity;
	class Renderer;
	class RenderItem;
	class VisualComponent;

	class ComponentRegister
		: private NonCopyable
		, private NonMoveable
	{
	protected:
		ComponentRegister();
	public:
		virtual ~ComponentRegister();
		void init(Renderer* render);

		void registerEntity(Entity* entity);
	private:
		virtual void registerVisualComponent(Entity* entity, VisualComponent* visualComponent, Renderer* renerer) = 0;
	private:
		struct ComponentRegisterPrivate* _members;
	};
}