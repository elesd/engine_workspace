#pragma once

#include <engine/entityFramework/Component.h>

#include <engine/signalSlot/Signal.h>

namespace engine
{
	class TransformationComponent
		: public Component
	{
		friend class TransformationComponentAttachment;
	public:
		Signal<> transformationChanged;
	public:
		TransformationComponent();
		~TransformationComponent() override;

		TransformationComponent* getParentComponent() const;
		bool hasParentComponent() const;
		const std::vector<TransformationComponent*>& getChildrenComponent() const;

		void attachComponent(TransformationComponent* component);
		void detachComponent(TransformationComponent* component);

		const vec3& getWorldPosition() const;
		void setWorldPosition(const vec3&);

		const quat& getWorldRotation() const;
		void setWorldRotation(const quat&);

		const mat4& getWorldTransformation() const;
		const mat4& getInvWorldTransformation() const;

		const vec3& getLocalPosition() const;
		const quat& getLocalRotation() const;

		const mat4& getLocalTransformation() const;
		const mat4& getInvLocalTransformation() const;

		void setLocalPosition(const vec3& position);
		void setLocalRotation(const quat& rotation);

		void lookAt(const vec3& eyeDir, const vec3& up);
		vec3 getUpVector() const;
		vec3 getEyeDirection() const;
		vec3 getRightVector() const;
		TNBFrame getTNBFrame() const;

	protected:
		void recalclateLocalTransformation() const;
		void recalclateInvLocalTransformation() const;
		void recalclateWorldTransformation() const;
		void recalclateInvWorldTransformation() const;
		void recalculateWorldRotation() const;
		void recalculateWorldPosition() const;

	private:
		void onTransformationChanged();
		void onParentTransformationChanged();
		std::vector<TransformationComponent*>& accessChildren();
		void setParent(TransformationComponent*);
	private:
		void onRenderComponent(RenderContext*) override final;
		void onUpdateComponent() override final;
		std::unique_ptr<Component> cloneComponent() const override final;
	public:
		Signal<const vec3&> positionChanged;
		Signal<const quat&> rotationChanged;
	private:
		struct TransformationComponentPrivate* _members = nullptr;
	};
}