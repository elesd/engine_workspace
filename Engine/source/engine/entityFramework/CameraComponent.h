#pragma once

#include <engine/entityFramework/Component.h>

namespace engine
{
	class Window;
	class CameraComponent;

	class CameraSettings
	{
		friend class CameraComponent;
	public:
		CameraSettings(float nearPlane, float farPlane, float fov, bool ortho)
			: _nearPlane(nearPlane)
			, _farPlane(farPlane)
			, _fov(fov)
			, _ortho(ortho)
		{}

		float getNearPlane() const { return _nearPlane; }
		float getFarPlane() const { return _farPlane; }
		float getFov() const { return _fov; }
		bool isOrtho() const { return _ortho; }

	private:
		float _nearPlane = 0.0f;
		float _farPlane = 0.0f;
		float _fov = 0.0f;
		bool _ortho = 0.0f;
	};

	class CameraComponent
		: public Component
	{
	public:
		CameraComponent(Window* window, const CameraSettings& settings);
		~CameraComponent() override;
		const CameraSettings& getSettings() const;

		void setFov(float);
		void setNearPlane(float);
		void setFarPlane(float);

		void buildOrthographic();
		void buildPerspective();

		glm::mat4 getProjectionMatrix() const;

		glm::vec3 screenPointToWorldPoint(const glm::vec3& screenPosition) const;
		glm::vec3 worldPointToScreenPoint(const glm::vec3& worldPosition) const;

		glm::vec3 screenPointToViewport(const glm::vec3& screenPosition) const;
		glm::vec3 viewportToScreenPoint(const glm::vec3& viewportPosition) const;

		glm::vec3 viewportToWorldPoint(const glm::vec3& viewportPosition) const;
		glm::vec3 WorldPointToViewport(const glm::vec3& worldPosition) const;
	protected:
		void updateProjectionMatrix() const;
		void updateInvProjectionMatrix() const;
	private:
		void onRenderComponent(RenderContext*) override;
		void onUpdateComponent() override;
		std::unique_ptr<Component> cloneComponent() const override;
	private:
		struct CameraComponentPrivate* _members = nullptr;
	};
}
