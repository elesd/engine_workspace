#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>
#include <engine/signalSlot/IntermediateSlotHolder.h>

namespace engine
{
	class ComponentRegister;
	class RenderContext;
	class Render;
	class Scene;
	
	struct SceneManagerState
	{
		std::vector<Scene*> activeScenes;
		std::vector<Render*> activeRenderers;
		std::map<std::string, Render*> rendererMap;
		std::vector<Scene*> scenes;
	};

	class SceneManager final
		: private NonCopyable
		, private NonMoveable
		, public IntermediateSlotHolder
	{
		friend class Application;
		SceneManager();
	public:
		~SceneManager();

		Scene* createScene(const std::string& sceneName, RenderContext* context, const std::string& rendererName, std::unique_ptr<ComponentRegister>&& componentRegister);
		Scene* findScene(const std::string& sceneName) const;
		Render* findRenderForScene(const std::string& sceneName) const;
		void deleteScene(const std::string& sceneName);
		const std::vector<Render*>& getActiveScenesRenderer() const;
		const std::vector<Scene*>& getActiveScenes() const;
		const std::vector<Scene*>& getScenes() const;
		const SceneManagerState& getCurrentState() const;

		void update();
	private:
		void removeDeletedScenes();
	private:
		void whenSceneActivationChanged();
		void whenScenePriorityChanged();
	private:
		struct SceneManagerPrivate* _members = nullptr;
	};
}