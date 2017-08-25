#pragma once

#include <engine/entityFramework/Component.h>


namespace engine
{
	class Window;

	class ProjectionComponent
		: public Component
	{
	public:
		ProjectionComponent(Window* window, float nearPlane, float farPlane);
		~ProjectionComponent() override;

		void setNearPlane(float);
		void setFarPlane(float);

		float getNearPlane() const;
		float getFarPlane() const;

		glm::mat4 getProjectionMatrix() const;
		glm::mat4 getInvProjectionMatrix() const;

		//glm::vec3 screenPointToWorldPoint(const glm::vec3& screenPosition) const;
		//glm::vec3 worldPointToScreenPoint(const glm::vec3& worldPosition) const;

		//glm::vec3 screenPointToViewport(const glm::vec3& screenPosition) const;
		//glm::vec3 viewportToScreenPoint(const glm::vec3& viewportPosition) const;

		//glm::vec3 viewportToWorldPoint(const glm::vec3& viewportPosition) const;
		//glm::vec3 WorldPointToViewport(const glm::vec3& worldPosition) const;
	protected:
		void updateProjectionMatrix() const;
		void updateInvProjectionMatrix() const;
	
	private:
		void onRenderComponent(RenderContext*) override;
		void onUpdateComponent() override;
		std::unique_ptr<Component> cloneComponent() const override;

	private:
		virtual glm::mat4 buildProjectionMatrix() = 0;
	private:
		struct ProjectionComponentPrivate* _members = nullptr;
	};
}
