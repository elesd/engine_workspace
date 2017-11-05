#pragma once

#include <engine/constraints/Lockable.h>

#include <engine/signalSlot/Signal.h>

namespace engine
{
	class Entity;
	class EntityContainer;
	class ComponentRegister;
	class SceneProxy;

	class Scene final
		: public Lockable<Scene>
	{
		friend class SceneManager;
		friend class SceneProxy;
	public:

		Signal<> sceneActivated;
		Signal<> sceneDeactivated;
		Signal<> scenePriorityChanged;
	private:
		explicit Scene(const std::string& sceneName, std::unique_ptr<ComponentRegister>&& componentRegister);
	public:
		~Scene();

		void registerEntity(std::unique_ptr<Entity>&& entity);
		std::unique_ptr<Entity> unregisterEntity(Entity* entity);
		std::vector<Entity*> getEntities() const;

		int32_t getRenderPriority() const;
		void setRenderPriority(int32_t);

		bool isActive() const;
		void activate();
		void deactivate();

		void update();

		const std::string& getName() const;

		SceneProxy* getProxy();
		void refreshByProxy();
	private:
		const EntityContainer& getEntityContainer() const;
	private:
		struct ScenePrivate* _members = nullptr;
	};
}