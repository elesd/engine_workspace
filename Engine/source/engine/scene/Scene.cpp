#include <stdafx.h>
#include <engine/scene/Scene.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/entityFramework/Entity.h>

#include <engine/functional/functions.h>

#include <engine/scene/ComponentRegister.h>

namespace engine
{
	struct SceneEntityCache
	{
		std::vector<Entity*> entities;
	};

	struct ScenePrivate
	{
		std::string name;
		int32_t renderPrioirty = 0;
		bool active = true;
		std::unique_ptr<ComponentRegister> componentRegister;
		std::vector<std::unique_ptr<Entity>> entityContainer;
		SceneEntityCache cache;
		ScenePrivate(const std::string& sceneName, std::unique_ptr<ComponentRegister>&& componentRegister)
			:name(sceneName), componentRegister(std::move(componentRegister))
		{

		}
	};

	Scene::Scene(const std::string& sceneName, std::unique_ptr<ComponentRegister>&& componentRegister)
		: _members(new ScenePrivate(sceneName, std::move(componentRegister)))
	{

	}

	Scene::~Scene()
	{
		delete _members;
		_members = nullptr;
	}

	void Scene::registerEntity(std::unique_ptr<Entity>&& entity)
	{
		_members->componentRegister->registerEntity(entity.get());
		_members->cache.entities.push_back(entity.get());
		_members->entityContainer.push_back(std::move(entity));
	}

	std::unique_ptr<Entity> Scene::unregisterEntity(Entity* entity)
	{
		{
			auto it = std::remove(_members->cache.entities.begin(), _members->cache.entities.end(), entity);
			_members->cache.entities.erase(it, _members->cache.entities.end());
		}

		{
			auto it = std::remove_if(_members->entityContainer.begin(), _members->entityContainer.end(),
									 PointerEqualTo<Entity>(entity));
			_members->entityContainer.erase(it, _members->entityContainer.end());
		}
	}

	std::vector<Entity*> Scene::getEntities() const
	{
		return _members->cache.entities;
	}

	std::vector<Entity*> Scene::findCameraEntities() const
	{
		std::vector<Entity*> result;
		std::copy_if(_members->cache.entities.begin(), _members->cache.entities.end(), std::back_inserter(result),
					 [](Entity* e)->bool { return e->hasCameraComponent(); });
		return result;
	}

	std::vector<Entity*> Scene::findEntitiesByTag(uint32_t tag)
	{
		std::vector<Entity*> result;
		std::copy_if(_members->cache.entities.begin(), _members->cache.entities.end(), std::back_inserter(result),
					 [tag](Entity* e)->bool { return e->getTag() == tag; });
		return result;
	}

	std::vector<Entity*> Scene::findEntitiesByName(const std::string& name)
	{
		std::vector<Entity*> result;
		std::copy_if(_members->cache.entities.begin(), _members->cache.entities.end(), std::back_inserter(result),
					 [&name](Entity* e)->bool { return e->getName() == name; });
		return result;
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
		for(Entity* e : _members->cache.entities)
		{
			e->update();
		}
	}

	const std::string& Scene::getName() const
	{
		return _members->name;
	}
}