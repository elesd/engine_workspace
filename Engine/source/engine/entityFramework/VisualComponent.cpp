#include <stdafx.h>
#include <engine/entityFramework/VisualComponent.h>
///////////////////////////////////////////////////////////////////////////////

namespace engine
{
	struct VisualComponentPrivate
	{
		bool hiddenInGame = true;
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

	bool VisualComponent::isHiddenInGame() const
	{
		return _members->hiddenInGame;
	}

	void VisualComponent::setHiddenInGame(bool v)
	{
		_members->hiddenInGame = v;
	}

	void VisualComponent::onRenderSceneComponent(RenderContext* renderContext) 
	{
		onRenderVisualComponent(renderContext);
	}

	void VisualComponent::onUpdateSceneComponent()
	{
		onUpdateVisualComponent();
	}

	std::unique_ptr<Component> VisualComponent::cloneSceneComponent() const
	{
		std::unique_ptr<Component> result = cloneVisualComponent();
		static_cast<VisualComponent*>(result.get())->setHiddenInGame(isHiddenInGame());
		return result;
	}
}