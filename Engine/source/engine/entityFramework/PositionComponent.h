#pragma once

#include <engine/entityFramework/Component.h>

#include <engine/signalSlot/Signal.h>

namespace engine
{
	class PositionComponent
		: public Component
	{
	public:
		PositionComponent();
		~PositionComponent() override;

		const glm::vec3& getPosition() const;
		const glm::quat& getRotation() const;

		const glm::mat4& getTransformation() const;

		void setPosition(const glm::vec3& position);
		void setRotation(const glm::quat& rotation);

	protected:
		void recalclateTransformation() const;
	private:
		void onRenderComponent(RenderContext*) override;
		void onUpdateComponent() override;
		std::unique_ptr<Component> cloneComponent() const override;
	public:
		Signal<const glm::vec3&> positionChanged;
		Signal<const glm::quat&> rotationChanged;
	private:
		struct PositionComponentPrivate* _members = nullptr;
	};
}