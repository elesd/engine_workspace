#include <stdafx.h>
#include <engine/entityFramework/SceneComponent.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/entityFramework/TransformationComponent.h>

namespace engine
{

	struct SceneComponentPrivate
	{
		std::unique_ptr<TransformationComponent> transformation;
		SceneComponentPrivate()
			: transformation(new TransformationComponent())
		{

		}
	};

	SceneComponent::SceneComponent()
		: _members(new SceneComponentPrivate())
	{
	}

	SceneComponent::~SceneComponent()
	{
		delete _members;
		_members = nullptr;
	}
	void SceneComponent::setTransformationComponent(std::unique_ptr<TransformationComponent>&& component)
	{
		ASSERT(component != nullptr);
		_members->transformation = std::move(component);
	}

	void SceneComponent::registerTransformationComponent(std::unique_ptr<TransformationComponent>&& component)
	{
		setTransformationComponent(std::move(component));
		onTransformationComponentSet();
	}

	const TransformationComponent* SceneComponent::getTransformationComponent() const
	{
		return _members->transformation.get();
	}

	TransformationComponent* SceneComponent::getTransformationComponent() 
	{
		return _members->transformation.get();
	}

	bool SceneComponent::hasTransformationComponent() const
	{
		return _members->transformation != nullptr;
	}

	void SceneComponent::onRenderComponent(RenderContext* renderContext)
	{
		if(hasTransformationComponent())
		{
			_members->transformation->onRender(renderContext);
		}
		onRenderSceneComponent(renderContext);
	}

	void SceneComponent::onUpdateComponent()
	{
		if(hasTransformationComponent())
		{
			_members->transformation->onUpdate();
		}
	}

	std::unique_ptr<Component> SceneComponent::cloneComponent() const
	{
		std::unique_ptr<Component> result = cloneSceneComponent();
		if(hasTransformationComponent)
		{
			std::unique_ptr<Component> cloneComponent = _members->transformation->clone();
			std::unique_ptr<TransformationComponent> cloneTransformation = common::static_unique_ptr_cast<TransformationComponent>(std::move(cloneComponent));
			static_cast<SceneComponent*>(result.get())->setTransformationComponent(std::move(cloneTransformation));
		}
		return result;
	}
}