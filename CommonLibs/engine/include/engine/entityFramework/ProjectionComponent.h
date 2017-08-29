#pragma once

#include <engine/entityFramework/Component.h>

#include <engine/signalSlot/Signal.h>


namespace engine
{
	class Window;

	class ProjectionComponent
		: public Component
	{
	public:
		Signal<> projectionChanged;
	public:
		ProjectionComponent(Window* window, float nearPlane, float farPlane);
		~ProjectionComponent() override;

		void setNearPlane(float);
		void setFarPlane(float);

		float getNearPlane() const;
		float getFarPlane() const;

		mat4 getProjectionMatrix() const;
		mat4 getInvProjectionMatrix() const;

		vec3 screenPointToViewport(const ScreenSpacePosition& screenPosition, float depth) const;
		ScreenSpacePosition viewportToScreenPoint(const vec3& viewportPosition) const;
		
	protected:
		void recalculateProjectionMatrix() const;
		void recalculateInvProjectionMatrix() const;
		void setProjectionMatrixDirty();
		Window* getWindow() const;
	private:
		void onRenderComponent(RenderContext*) override final;
		void onUpdateComponent() override final;
		std::unique_ptr<Component> cloneComponent() const override final;

	private:
		virtual mat4 buildProjectionMatrix() const = 0;
		virtual std::unique_ptr<Component> cloneProjectionComponent() const = 0;
	private:
		struct ProjectionComponentPrivate* _members = nullptr;
	};
}
