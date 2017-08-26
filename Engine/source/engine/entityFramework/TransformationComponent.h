#pragma once

#include <engine/entityFramework/Component.h>

#include <engine/signalSlot/Signal.h>

namespace engine
{
	class TransformationComponent
		: public Component
	{
	public:
		TransformationComponent();
		~TransformationComponent() override;

		const vec3& getPosition() const;
		const quat& getRotation() const;

		const mat4& getTransformation() const;

		void setPosition(const vec3& position);
		void setRotation(const quat& rotation);

	protected:
		void recalclateTransformation() const;
	private:
		void onRenderComponent(RenderContext*) override;
		void onUpdateComponent() override;
		std::unique_ptr<Component> cloneComponent() const override;
	public:
		Signal<const vec3&> positionChanged;
		Signal<const quat&> rotationChanged;
	private:
		struct TransformationComponentPrivate* _members = nullptr;
	};
}