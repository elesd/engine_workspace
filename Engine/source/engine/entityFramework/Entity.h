#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	class CameraComponent;
	class Component;
	class TransformationComponent;
	class VisualComponent;

	class Entity
		: private NonCopyable
		, private NonMoveable
	{
	public:
		Entity();
		virtual ~Entity();

		void registerCameraComponent(std::unique_ptr<CameraComponent>&& cameraComponent);
		void unregisterCameraComponent();
		void registerTransformationComponent(std::unique_ptr<TransformationComponent>&& positionComponent);
		void unregisterTransformationComponent();
		void registerVisualComponent(std::unique_ptr<VisualComponent>&& visualComponent);
		void unregisterVisualComponent(VisualComponent* component);

		CameraComponent* getCameraComponent();
		const CameraComponent* getCameraComponent() const;
		bool hasCameraComponent() const;

		TransformationComponent* getTransformationComponent();
		const TransformationComponent* getTransformationComponent() const;
		bool hasTransformationComponent() const;

		std::vector<VisualComponent*> getVisualComponents();
		const std::vector<VisualComponent*>& getVisualComponents() const;

		void registerCustomComponent(std::unique_ptr<Component>&& customComponent);
		void unregisterCustomComponent(Component* customComponent);

		std::vector<Component*> findCustomComponentsByTag(uint32_t tag) const;

		std::unique_ptr<Entity> clone() const;
	private:
		virtual std::unique_ptr<Entity> cloneEntity() const;

	private:
		struct EntityPrivate* _members = nullptr;
	};
}