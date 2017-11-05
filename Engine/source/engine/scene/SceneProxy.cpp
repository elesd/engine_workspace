#include <stdafx.h>
#include <engine/scene/SceneProxy.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/entityFramework/Entity.h>
#include <engine/entityFramework/EntityContainer.h>

#include <engine/functional/functions.h>

#include <engine/scene/Scene.h>

namespace engine
{
	void SceneProxySyncDelegate::sync(SceneProxy* sceneProxy)
	{
		sceneProxy->syncWithOrigin();
	}

	struct SceneProxyPrivate
	{
		std::vector<Entity*> registeredEntities;
		std::vector<Entity*> unregisteredEntities;
		EntityContainer entityContainer;
		bool active = true;
		Scene* origin = nullptr;
		explicit SceneProxyPrivate(Scene* origin) : origin(origin)
		{
		}
	};

	SceneProxy::SceneProxy(Scene* origin)
		:_members(new SceneProxyPrivate(origin))
	{

	}

	SceneProxy::~SceneProxy()
	{
		delete _members;
		_members = nullptr;
	}

	void SceneProxy::registerEntity(std::unique_ptr<Entity>&& entity)
	{
		_members->registeredEntities.push_back(entity.get());
		_members->entityContainer.add(std::move(entity));
	}

	std::unique_ptr<Entity> SceneProxy::unregisterEntity(Entity* entity)
	{
		_members->unregisteredEntities.push_back(entity);
		std::unique_ptr<Entity> result = _members->entityContainer.remove(entity);
		return result;
	}

	std::vector<Entity*> SceneProxy::getEntities() const
	{
		return _members->entityContainer.getEntities();
	}

	std::vector<Entity*> SceneProxy::findCameraEntities() const
	{
		std::vector<Entity*> result;
		std::copy_if(getEntities().begin(), getEntities().end(), std::back_inserter(result),
					 [](Entity* e)->bool { return e->hasCameraComponent(); });
		return result;
	}

	std::vector<Entity*> SceneProxy::findEntitiesByTag(uint32_t tag) const
	{
		std::vector<Entity*> result;
		std::copy_if(getEntities().begin(), getEntities().end(), std::back_inserter(result),
					 [tag](Entity* e)->bool { return e->getTag() == tag; });
		return result;
	}

	std::vector<Entity*> SceneProxy::findEntitiesByName(const std::string& name) const
	{
		std::vector<Entity*> result;
		std::copy_if(getEntities().begin(), getEntities().end(), std::back_inserter(result),
					 [&name](Entity* e)->bool { return e->getName() == name; });
		return result;
	}

	const std::string& SceneProxy::getName() const
	{
		return _members->origin->getName();
	}

	bool SceneProxy::isActive() const
	{
		return _members->active;
	}

	void SceneProxy::activate()
	{
		_members->active = true;
	}

	void SceneProxy::deactivate()
	{
		_members->active = false;
	}

	void SceneProxy::syncWithOrigin()
	{
		GuardedObject<Scene*> sceneOrigin = _members->origin->lock();
		delegateChangesToOrigin();
		initFromOrigin();
	}

	void SceneProxy::initFromOrigin()
	{
		_members->entityContainer.clear();
		// WARNING DeapCopy!
		_members->entityContainer = _members->origin->getEntityContainer();
	}

	void SceneProxy::delegateChangesToOrigin()
	{
		if(isActive() && !_members->origin->isActive())
		{
			_members->origin->activate();
		}
		else if(!isActive() && _members->origin->isActive())
		{
			_members->origin->deactivate();
		}

		for(Entity* e : _members->registeredEntities)
		{
			_members->origin->registerEntity(e->clone());
		}
		for(Entity* e : _members->unregisteredEntities)
		{
			_members->origin->unregisterEntity(e);
		}
		_members->registeredEntities.clear();
		_members->unregisteredEntities.clear();
	}

}