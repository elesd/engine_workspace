#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	class TransformationComponent;
	class VisualComponent;

	class Entity
		: private NonCopyable
		, private NonMoveable
	{
	public:
		Entity();
		virtual ~Entity();

		void setTransformationComponent(std::unique_ptr<TransformationComponent>&& positionComponent);
		void setVisualComponent(std::unique_ptr<VisualComponent>&& meshComponent);

		TransformationComponent* getTransformationComponent();
		const TransformationComponent* getTransformationComponent() const;

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