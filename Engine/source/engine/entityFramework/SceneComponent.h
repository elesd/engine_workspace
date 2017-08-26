#pragma once

#include <engine/entityFramework/Component.h>

namespace engine
{
	class TransformationComponent;

	class SceneComponent
		: public Component
	{
	public:
		SceneComponent();
		~SceneComponent() override;

		void registerTransformationComponent(std::unique_ptr<TransformationComponent>&&);
		const TransformationComponent* getTransformationComponent() const;
		TransformationComponent* getTransformationComponent();

		bool hasTransformationComponent() const;
	protected:
		void setTransformationComponent(std::unique_ptr<TransformationComponent>&&);

	private:
		void onRenderComponent(RenderContext*) override final;
		void onUpdateComponent() override final;
		std::unique_ptr<Component> cloneComponent() const override final;
	private:
		virtual void onTransformationComponentSet() {};
	private:
		virtual void onRenderSceneComponent(RenderContext*) = 0;
		virtual void onUpdateSceneComponent() = 0;
		virtual std::unique_ptr<Component> cloneSceneComponent() const = 0;
	private:
		struct SceneComponentPrivate* _members = nullptr;
	};
}