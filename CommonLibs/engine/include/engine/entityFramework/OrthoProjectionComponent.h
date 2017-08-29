#pragma once

#include <engine/entityFramework/ProjectionComponent.h>

namespace engine
{
	struct OrthogonalProjectionSettings
	{
		OrthogonalProjectionSettings(float left, float right, float top, float bottom, float nearPlane, float farPlane)
			: left(left)
			, right(right)
			, top(top)
			, bottom(bottom)
			, nearPlane(nearPlane)
			, farPlane(farPlane)
		{		}

		float left = 0.0f;
		float right = 0.0f;
		float top = 0.0f;
		float bottom = 0.0f;
		float nearPlane = 0.0f;
		float farPlane = 0.0f;
	};

	class OrthoProjectionComponent
		: public ProjectionComponent
	{
	public:
		OrthoProjectionComponent(Window* window, const OrthogonalProjectionSettings& settings);
		~OrthoProjectionComponent() override;

		float getLeft() const;
		void setLeft(float);

		float getRight() const;
		void setRight(float);

		float getTop() const;
		void setTop(float);

		float getBottom() const;
		void setBottom(float);

	private:
		mat4 buildProjectionMatrix() const override;
		std::unique_ptr<Component> cloneProjectionComponent() const override;

	private:
		struct OrthoProjectionComponentPrivate* _members = nullptr;
	};
}