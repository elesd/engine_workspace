#pragma once

#include <engine/entityFramework/SceneComponent.h>

#include <engine/signalSlot/IntermediateSlotHolder.h>

namespace engine
{
	class Window;
	class PerspProjectionComponent;
	class ProjectionComponent;
	class OrthoProjectionComponent;
	class TransformationComponent;

	struct PerspectiveProjectionSettings;
	struct OrthogonalProjectionSettings;

	class CameraComponent
		: public SceneComponent
		, public IntermediateSlotHolder
	{
	private:
		CameraComponent();
		explicit CameraComponent(const vec3& worldPosition);
	public:
		CameraComponent(Window* window, const PerspectiveProjectionSettings& settings, const vec3& worldPosition);
		CameraComponent(Window* window, const OrthogonalProjectionSettings& settings, const vec3& worldPosition);
		CameraComponent(Window* window, const OrthogonalProjectionSettings& orthoSettings, const PerspectiveProjectionSettings& perspSettings, const vec3& worldPosition, bool isOrtho);
		~CameraComponent() override;

		void registerOrthogonalProjection(std::unique_ptr<OrthoProjectionComponent>&& projection);
		void registerPerspectiveProjection(std::unique_ptr<PerspProjectionComponent>&& projection);

		void activatePerspectiveProjection();
		void activateOrthogonalProjection();

		const OrthoProjectionComponent* getOrthogonalProjection() const;
		OrthoProjectionComponent* getOrthogonalProjection();
		const PerspProjectionComponent* getPerspectiveProjection() const;
		PerspProjectionComponent* getPerspectiveProjection();
		
		bool hasOrthogonalProjection() const;
		bool hasPerspectiveProjection() const;

		bool isOrthographic() const;

		vec3 screenPointToWorldPoint(const ScreenSpacePosition& screenPosition, float depth) const;
		ScreenSpacePosition worldPointToScreenPoint(const vec3& worldPosition) const;

		vec3 screenPointToViewport(const ScreenSpacePosition& screenPosition, float depth) const;
		ScreenSpacePosition viewportToScreenPoint(const vec3& viewportPosition) const;

		vec3 viewportToWorldPoint(const vec3& viewportPosition) const;
		vec3 WorldPointToViewport(const vec3& worldPosition) const;

	protected:
		void setOrthogonalProjection(std::unique_ptr<OrthoProjectionComponent>&& projection);
		void setPerspectiveProjection(std::unique_ptr<PerspProjectionComponent>&& projection);
		void forceActivateOrthogonalProjection();
		void forceActivatePerspectiveProjection();
	private:
		void recalculatePVTransformation() const;
		void recalculateInvPVTransformation() const;
		const ProjectionComponent* getActiveProjection() const;
		ProjectionComponent* getActiveProjection();
		bool isValidComponent() const;
	private:
		void onTransformationComponentSet() override;
		void onRenderSceneComponent(RenderContext*) override final;
		void onUpdateSceneComponent() override final;
		std::unique_ptr<Component> cloneSceneComponent() const override final;

	private:
		void whenTransformationChanged();
		void whenProjectionChanged();
	private:
		struct CameraComponentPrivate* _members = nullptr;
	};
}