#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	class Scene;
	class SceneProxy;
	class Entity;

	class SceneProxySyncDelegate
	{
		friend class Scene;
		static void sync(SceneProxy* sceneProxy);
	};

	class SceneProxy
		: private NonCopyable
		, private NonMoveable
	{
		friend class SceneProxySyncDelegate;
	public:
		explicit SceneProxy(Scene* origin);
		~SceneProxy();

		void registerEntity(std::unique_ptr<Entity>&& entity);
		std::unique_ptr<Entity> unregisterEntity(Entity* entity);
		std::vector<Entity*> getEntities() const;
		std::vector<Entity*> findCameraEntities() const;
		std::vector<Entity*> findEntitiesByTag(uint32_t tag) const;
		std::vector<Entity*> findEntitiesByName(const std::string& name) const;

		const std::string& getName() const;
		bool isActive() const;
		void activate();
		void deactivate();

	private:
		void syncWithOrigin();
		void initFromOrigin();
		void delegateChangesToOrigin();
	private:
		struct SceneProxyPrivate* _members = nullptr;
	};
}