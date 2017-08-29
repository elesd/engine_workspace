#pragma once

#include <engine/entityFramework/ProjectionComponent.h>

namespace engine
{
	struct PerspectiveProjectionSettings
	{
		PerspectiveProjectionSettings(float fov, float nearPlane, float farPlane)
			: fov(fov)
			, nearPlane(nearPlane)
			, farPlane(farPlane)
		{
		}

		float fov = 0.0f;
		float nearPlane = 0.0f;
		float farPlane = 0.0f;
	};

	class PerspProjectionComponent
		: public ProjectionComponent
	{
	public:
		PerspProjectionComponent(Window* window, const PerspectiveProjectionSettings& settings);
		~PerspProjectionComponent() override;

		float getFov() const;
		void setFov(float);

	private:
		mat4 buildProjectionMatrix() const override;
		std::unique_ptr<Component> cloneProjectionComponent() const override;

	private:
		struct PerspProjectionComponentPrivate* _members = nullptr;
	};
}