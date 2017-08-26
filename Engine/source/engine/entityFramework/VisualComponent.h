#pragma once

#include <engine/entityFramework/SceneComponent.h>

namespace engine
{
	class Material;

	class VisualComponent
		: public SceneComponent
	{
	protected:
		VisualComponent();
	public:
		~VisualComponent() override;

		std::vector<Material*> collectMaterials() const;
		bool isHiddenInGame() const;
		void setHiddenInGame(bool);

	private:
		void onRenderSceneComponent(RenderContext*) override final;
		void onUpdateSceneComponent() override final;
		std::unique_ptr<Component> cloneSceneComponent() const override final;
	private:
		virtual std::vector<Material*> collectMaterialsImpl() const = 0;
		virtual void onRenderVisualComponent(RenderContext*) = 0;
		virtual void onUpdateVisualComponent() = 0;
		virtual std::unique_ptr<Component> cloneVisualComponent() const = 0;
	private:
		struct VisualComponentPrivate* _members = nullptr;
	};
}