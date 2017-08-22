#pragma once

#include <engine/entityFramework/Component.h>

namespace engine
{
	class Material;

	class VisualComponent
		: public Component
	{
	protected:
		VisualComponent();
	public:
		~VisualComponent() override;

		std::vector<Material*> collectMaterials() const;
		bool isVisible() const;
		void setVisible(bool);
	private:
		void onRenderComponent(RenderContext*) override;
		void onUpdateComponent() override;
		std::unique_ptr<Component> cloneComponent() const override;
	private:
		virtual std::vector<Material*> collectMaterialsImpl() const = 0;
		virtual void onRenderVisualComponent(RenderContext*) = 0;
		virtual void onUpdateVisualComponent() = 0;
		virtual std::unique_ptr<Component> cloneVisualComponent() const = 0;
	private:
		struct VisualComponentPrivate* _members = nullptr;
	};
}