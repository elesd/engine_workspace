#pragma once

#include <engine/signalSlot/Signal.h>

namespace engine
{
	class Entity;
	class ComponentRegister;
	class Render;
	class Scene final
	{
		friend class SceneManager;
	public:
		Signal<> sceneActivated;
		Signal<> sceneDeactivated;
	private:
		explicit Scene(const std::string& sceneName, std::unique_ptr<ComponentRegister>&& componentRegister);
	public:
		~Scene();

		void registerEntity(std::unique_ptr<Entity>&& entity);
		std::unique_ptr<Entity> unregisterEntity(Entity* entity);
		std::vector<Entity*> getEntities() const;
		std::vector<Entity*> findCameraEntities() const;
		std::vector<Entity*> findEntitiesByTag(uint32_t tag);
		std::vector<Entity*> findEntitiesByName(const std::string& name);

		int32_t getRenderPriority() const;
		void setRenderPriority(int32_t) const;

		bool isActive() const;
		void activate();
		void deactivate();

		void update();

		const std::string& getName() const;
	private:
		struct ScenePrivate* _members = nullptr;
	};
}