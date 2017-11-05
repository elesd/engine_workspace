#pragma once


namespace engine
{
	class Entity;

	class EntityContainer
	{
	public:
		EntityContainer();
		EntityContainer(const EntityContainer& o);
		EntityContainer(EntityContainer&& o);
		~EntityContainer();

		EntityContainer& operator=(const EntityContainer& o);
		EntityContainer& operator=(EntityContainer&& o);

		void add(std::unique_ptr<Entity>&& entity);
		std::unique_ptr<Entity> remove(Entity* entity);
		bool hasEntity(Entity* entity) const;
		void clear();
		bool isEmpty() const;
		std::vector<Entity*> getEntities() const;

	private:
		void cloneFrom(const EntityContainer& o);
	private:
		struct EntityContainerPrivate* _members = nullptr;

	};
}