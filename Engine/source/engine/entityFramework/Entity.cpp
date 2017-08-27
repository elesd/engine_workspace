#include <stdafx.h>
#include <engine/entityFramework/Entity.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/entityFramework/CameraComponent.h>
#include <engine/entityFramework/Component.h>
#include <engine/entityFramework/TransformationComponent.h>
#include <engine/entityFramework/VisualComponent.h>

#include <engine/functional/functions.h>

namespace engine
{
	struct EntityComponentCache
	{
		std::vector<VisualComponent*> visuals;
		std::vector<Component*> customs;
	};

	struct EntityPrivate
	{
		std::unique_ptr<CameraComponent> cameraComponent;
		std::unique_ptr<TransformationComponent> transformation;
		std::vector<std::unique_ptr<VisualComponent>> visualComponentsContainer;
		std::vector<std::unique_ptr<Component>> customComponentContainer;
		EntityComponentCache cache;
	};

	Entity::Entity()
		: _members(new EntityPrivate())
	{

	}

	Entity::~Entity()
	{
		delete _members;
		_members = nullptr;
	}

	void Entity::registerCameraComponent(std::unique_ptr<CameraComponent>&& cameraComponent)
	{
		_members->cameraComponent = std::move(cameraComponent);
		if(hasTransformationComponent())
		{
			_members->transformation->attachComponent(_members->cameraComponent->getTransformationComponent());
		}
	}

	void Entity::unregisterCameraComponent()
	{
		_members->cameraComponent = nullptr;
	}

	void Entity::registerTransformationComponent(std::unique_ptr<TransformationComponent>&& positionComponent)
	{
		_members->transformation = std::move(positionComponent);
		for(VisualComponent* component : _members->cache.visuals)
		{
			_members->transformation->attachComponent(component->getTransformationComponent());
		}
		if(hasCameraComponent())
		{
			_members->transformation->attachComponent(_members->cameraComponent->getTransformationComponent());
		}
	}

	void Entity::unregisterTransformationComponent()
	{
		_members->transformation = nullptr;
	}

	void Entity::registerVisualComponent(std::unique_ptr<VisualComponent>&& visualComponent)
	{
		if(hasTransformationComponent())
		{
			_members->transformation->attachComponent(visualComponent->getTransformationComponent());
		}
		_members->cache.visuals.push_back(visualComponent.get());
		_members->visualComponentsContainer.push_back(visualComponent);
	}

	void Entity::unregisterVisualComponent(VisualComponent* component)
	{
		{
			auto it = std::remove(_members->cache.visuals.begin(), _members->cache.visuals.end(), component);
			_members->cache.visuals.erase(it, _members->cache.visuals.end());
		}
		{
			auto it = std::remove_if(_members->visualComponentsContainer.begin(), _members->visualComponentsContainer.end(),
									 PointerEqualTo<VisualComponent>(component));
			_members->visualComponentsContainer.erase(it, _members->visualComponentsContainer.end());
		}
	}

	CameraComponent* Entity::getCameraComponent()
	{
		return _members->cameraComponent.get();
	}

	const CameraComponent* Entity::getCameraComponent() const
	{
		return _members->cameraComponent.get();
	}

	bool Entity::hasCameraComponent() const
	{
		return _members->cameraComponent != nullptr;
	}

	TransformationComponent* Entity::getTransformationComponent()
	{
		return _members->transformation.get();
	}

	const TransformationComponent* Entity::getTransformationComponent() const
	{
		return _members->transformation.get();
	}

	bool Entity::hasTransformationComponent() const
	{
		return _members->transformation != nullptr;
	}

	std::vector<VisualComponent*> Entity::getVisualComponents()
	{
		return _members->cache.visuals;
	}

	const std::vector<VisualComponent*>& Entity::getVisualComponents() const
	{
		return _members->cache.visuals;
	}

	void Entity::registerCustomComponent(std::unique_ptr<Component>&& customComponent)
	{
		_members->cache.customs.push_back(customComponent.get());
		_members->customComponentContainer.push_back(std::move(customComponent));
	}

	void Entity::unregisterCustomComponent(Component* customComponent)
	{
		{
			auto it = std::remove(_members->cache.customs.begin(), _members->cache.customs.end(), customComponent);
			_members->cache.customs.erase(it, _members->cache.customs.end());
		}
		{
			auto it = std::remove_if(_members->customComponentContainer.begin(), _members->customComponentContainer.end(),
									 PointerEqualTo<Component>(customComponent));
			_members->customComponentContainer.erase(it, _members->customComponentContainer.end());
		}
	}


	std::vector<Component*> Entity::findCustomComponentsByTag(uint32_t tag) const
	{
		std::vector<Component*> result;
		std::copy_if(_members->cache.customs.begin(), _members->cache.customs.end(), std::back_inserter(result),
					 [tag](const Component* c)->bool { return c->getTag() == tag; });
		return result;
	}

	std::unique_ptr<Entity> Entity::clone() const
	{
		std::unique_ptr<Entity> result = cloneEntity();
		if(hasTransformationComponent())
		{
			std::unique_ptr<TransformationComponent> cloneComponent = common::static_unique_ptr_cast<TransformationComponent>(_members->transformation->clone());
			result->registerTransformationComponent(std::move(cloneComponent));
		}
		for(const VisualComponent* component : _members->cache.visuals)
		{
			std::unique_ptr<VisualComponent> cloneComponent = common::static_unique_ptr_cast<VisualComponent>(component->clone());
			result->registerVisualComponent(std::move(cloneComponent));
		}
		for(const Component* component : _members->cache.customs)
		{
			std::unique_ptr<Component> cloneComponent = component->clone();
			result->registerCustomComponent(std::move(cloneComponent));
		}
		return result;
	}

	std::unique_ptr<Entity> Entity::cloneEntity() const
	{
		return std::make_unique<Entity>();
	}

}