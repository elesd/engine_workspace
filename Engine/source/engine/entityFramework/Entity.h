#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	class PositionComponent;
	class VisualComponent;

	class Entity
		: private NonCopyable
		, private NonMoveable
	{
	public:
		Entity();
		virtual ~Entity();

		void setPositionComponent(std::unique_ptr<PositionComponent>&& positionComponent);
		void setVisualComponent(std::unique_ptr<VisualComponent>&& meshComponent);

		PositionComponent* getPositionComponent();
		const PositionComponent* getPositionComponent() const;

		VisualComponent* getVisualComponent();
		const VisualComponent* getVisualComponent() const;

		void addCustomComponent(std::unique_ptr<Component>&& customComponent);

		std::vector<Component*> findComponentsByTag(uint32_t tag);

		std::unique_ptr<Entity> clone() const;
	private:
		virtual std::unique_ptr<Entity> cloneEntity() const {};

	private:
		struct EntityPrivate* _members = nullptr;
	};
}