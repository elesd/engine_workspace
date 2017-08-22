#include <stdafx.h>
#include <engine/entityFramework/VisualComponent.h>
///////////////////////////////////////////////////////////////////////////////

namespace engine
{
	struct VisualComponentPrivate
	{
		bool visible = true;
	};

	VisualComponent::VisualComponent()
		: _members(new VisualComponentPrivate())
	{

	}

	VisualComponent::~VisualComponent()
	{
		delete _members;
		_members = nullptr;
	}

	std::vector<Material*> VisualComponent::collectMaterials() const
	{
		return collectMaterialsImpl();
	}

	bool VisualComponent::isVisible() const
	{
		return _members->visible;
	}

	void VisualComponent::setVisible(bool v)
	{
		_members->visible = v;
	}

	void VisualComponent::onRenderComponent(RenderContext* renderContext) 
	{
		onRenderVisualComponent(renderContext);
	}

	void VisualComponent::onUpdateComponent()
	{
		onUpdateVisualComponent();
	}

	std::unique_ptr<Component> VisualComponent::cloneComponent() const
	{
		std::unique_ptr<Component> result = cloneVisualComponent();
		static_cast<VisualComponent*>(result.get())->setVisible(isVisible());
		return result;
	}
}