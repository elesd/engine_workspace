#include <stdafx.h>
#include <engine/entityFramework/EntityContainer.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/entityFramework/Entity.h>

#include <engine/functional/functions.h>

namespace engine
{
	struct EntityCache
	{
		std::vector<Entity*> entities;
	};
	struct EntityContainerPrivate
	{
		EntityCache cache;
		std::vector<std::unique_ptr<Entity>> entities;
	};



	EntityContainer::EntityContainer()
		: _members(new EntityContainerPrivate())
	{

	}

	EntityContainer::EntityContainer(const EntityContainer& o)
		: _members(new EntityContainerPrivate())
	{
		cloneFrom(o);
	}

	EntityContainer::EntityContainer(EntityContainer&& o)
		: _members(o._members)
	{
		o._members = nullptr;
	}

	EntityContainer::~EntityContainer()
	{
		delete _members;
		_members = nullptr;
	}

	EntityContainer& EntityContainer::operator=(const EntityContainer& o)
	{
		clear();
		cloneFrom(o);
		return *this;
	}

	EntityContainer& EntityContainer::operator=(EntityContainer&& o)
	{
		delete _members;
		_members = o._members;
		o._members = nullptr;
		return *this;
	}

	void EntityContainer::add(std::unique_ptr<Entity>&& entity)
	{
		_members->cache.entities.push_back(entity.get());
		_members->entities.push_back(std::move(entity));
	}

	std::unique_ptr<Entity> EntityContainer::remove(Entity* entity)
	{
		{
			auto it = std::remove(_members->cache.entities.begin(), _members->cache.entities.end(), entity);
			_members->cache.entities.erase(it, _members->cache.entities.end());
		}
		std::unique_ptr<Entity> result(entity);
		{
			for(std::unique_ptr<Entity>& entityPtr : _members->entities)
			{
				if(entityPtr.get() == entity)
				{
					entityPtr.release();
				}
			}
			auto it = std::remove_if(_members->entities.begin(), _members->entities.end(),
									 [](const std::unique_ptr<Entity>& e)->bool { return e == nullptr; });
			_members->entities.erase(it, _members->entities.end());
		}
		return result;
	}

	bool EntityContainer::hasEntity(Entity* entity) const
	{
		return std::find(_members->cache.entities.begin(), _members->cache.entities.end(), entity) != _members->cache.entities.end();
	}

	void EntityContainer::clear()
	{
		_members->cache.entities.clear();
		_members->entities.clear();
	}

	bool EntityContainer::isEmpty() const
	{
		ASSERT(_members->cache.entities.empty() == _members->entities.empty());
		return _members->entities.empty();
	}

	std::vector<Entity*> EntityContainer::getEntities() const
	{
		return _members->cache.entities;
	}

	void EntityContainer::cloneFrom(const EntityContainer& o)
	{
		for(const std::unique_ptr<Entity>& e : o._members->entities)
		{
			add(e->clone());
		}
	}
}