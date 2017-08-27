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

		void registerTransformationComponent(std::unique_ptr<TransformationComponent>&& positionComponent);
		void registerVisualComponent(std::unique_ptr<VisualComponent>&& meshComponent);

		TransformationComponent* getTransformationComponent();
		const TransformationComponent* getTransformationComponent() const;

		std::vector<VisualComponent*> getVisualComponents();
		const std::vector<VisualComponent*>& getVisualComponent() const;

		void registerCustomComponent(std::unique_ptr<Component>&& customComponent);

		std::vector<Component*> findComponentsByTag(uint32_t tag);

		std::unique_ptr<Entity> clone() const;
	private:
		virtual std::unique_ptr<Entity> cloneEntity() const {};

	private:
		struct EntityPrivate* _members = nullptr;
	};
}