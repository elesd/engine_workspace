#include <stdafx.h>
#include <engine/scene/Scene.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/entityFramework/Entity.h>
#include <engine/entityFramework/EntityContainer.h>

#include <engine/functional/functions.h>

#include <engine/scene/ComponentRegister.h>
#include <engine/scene/SceneProxy.h>

namespace engine
{
	struct ScenePrivate
	{
		std::string name;
		int32_t renderPrioirty = 0;
		bool active = true;
		std::unique_ptr<ComponentRegister> componentRegister;
		std::unique_ptr<SceneProxy> proxy;
		EntityContainer entityContainer;
		ScenePrivate(const std::string& sceneName, std::unique_ptr<ComponentRegister>&& componentRegister)
			:name(sceneName), componentRegister(std::move(componentRegister))
		{

		}
	};

	Scene::Scene(const std::string& sceneName, std::unique_ptr<ComponentRegister>&& componentRegister)
		: _members(new ScenePrivate(sceneName, std::move(componentRegister)))
	{
		_members->proxy.reset(new SceneProxy(this));
	}

	Scene::~Scene()
	{
		delete _members;
		_members = nullptr;
	}

	void Scene::registerEntity(std::unique_ptr<Entity>&& entity)
	{
		_members->componentRegister->registerEntity(entity.get());
		_members->entityContainer.add(std::move(entity));
	}

	std::unique_ptr<Entity> Scene::unregisterEntity(Entity* entity)
	{
		if(_members->entityContainer.isEmpty())
		{
			return nullptr;
		}

		std::unique_ptr<Entity> result = _members->entityContainer.remove(entity);
		
		return result;
	}

	std::vector<Entity*> Scene::getEntities() const
	{
		return _members->entityContainer.getEntities();
	}

	int32_t Scene::getRenderPriority() const
	{
		return _members->renderPrioirty;
	}

	void Scene::setRenderPriority(int32_t priority)
	{
		if(priority != _members->renderPrioirty)
		{
			_members->renderPrioirty = priority;
			scenePriorityChanged.emit();
		}
	}

	bool Scene::isActive() const
	{
		return _members->active;
	}

	void Scene::activate()
	{
		if(!isActive())
		{
			_members->active = true;
			sceneActivated.emit();
		}
	}

	void Scene::deactivate()
	{
		if(isActive())
		{
			_members->active = false;
			sceneDeactivated.emit();
		}
	}

	void Scene::update()
	{
		for(Entity* e : getEntities())
		{
			e->update();
		}
	}

	const std::string& Scene::getName() const
	{
		return _members->name;
	}

	SceneProxy* Scene::getProxy()
	{
		return _members->proxy.get();
	}

	void Scene::refreshByProxy()
	{
		SceneProxySyncDelegate::sync(getProxy());
	}

	const EntityContainer& Scene::getEntityContainer() const
	{
		return _members->entityContainer;
	}
}