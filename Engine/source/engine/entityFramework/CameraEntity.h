#pragma once

#include <engine/entityFramework/Entity.h>

namespace engine
{
	class CameraComponent;
	class CameraSettings;
	class Window;

	class CameraEntity
		: public Entity
	{
	public:
		CameraEntity(Window* window, const CameraSettings& settings);
		~CameraEntity() override;

		CameraComponent* getCameraComponent();
		const CameraComponent* getCameraComponent() const;
	private:
		std::unique_ptr<Entity> cloneEntity() const override;
	private:
		struct CameraEntityPrivate* _members = nullptr;
	};
}