#include <stdafx.h>
#include <engine/scene/SceneManager.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/scene/Scene.h>
#include <engine/scene/ComponentRegister.h>

#include <engine/functional/functions.h>

#include <engine/render/Render.h>
#include <engine/render/RenderContext.h>


namespace engine
{
	

	struct SceneManagerPrivate
	{
		SceneManagerState currentState;
		std::vector<std::unique_ptr<Scene>> sceneContainer;
		std::vector<Scene*> scenesToRemove;
	};

	SceneManager::SceneManager()
		: _members(new SceneManagerPrivate())
	{

	}

	SceneManager::~SceneManager()
	{
		delete _members;
		_members = nullptr;
	}

	Scene* SceneManager::createScene(const std::string& sceneName, RenderContext* context, const std::string& rendererName, std::unique_ptr<ComponentRegister>&& componentRegister)
	{
		Render* renderer = context->findRender(rendererName);
		ASSERT(renderer != nullptr);
		componentRegister->init(renderer);

		std::unique_ptr<Scene> scene(new Scene(sceneName, std::move(componentRegister)));

		CONNECT_SIGNAL(scene.get(), sceneActivated, this, whenSceneActivationChanged);
		CONNECT_SIGNAL(scene.get(), sceneDeactivated, this, whenSceneActivationChanged);
		CONNECT_SIGNAL(scene.get(), scenePriorityChanged, this, whenScenePriorityChanged);
		_members->currentState.activeRenderers.push_back(renderer);
		_members->currentState.activeScenes.push_back(scene.get());
		_members->currentState.scenes.push_back(scene.get());

		_members->currentState.rendererMap.insert(std::make_pair(sceneName, renderer));
		_members->sceneContainer.push_back(std::move(scene));
		whenScenePriorityChanged();
		return _members->sceneContainer.back().get();
	}

	Scene* SceneManager::findScene(const std::string& sceneName) const
	{
		auto it = std::find_if(_members->currentState.scenes.begin(), _members->currentState.scenes.end(),
							   [&sceneName](const Scene* scene)->bool { return scene->getName() == sceneName; });
		return it != _members->currentState.scenes.end() ? *it : nullptr;
	}

	Render* SceneManager::findRenderForScene(const std::string& sceneName) const
	{
		auto it = _members->currentState.rendererMap.find(sceneName);
		return it != _members->currentState.rendererMap.end() ? it->second : nullptr;
	}

	void SceneManager::deleteScene(const std::string& sceneName)
	{
		while(Scene* scene = findScene(sceneName))
		{
			_members->scenesToRemove.push_back(scene);
			{
				auto it = std::remove(_members->currentState.activeScenes.begin(), _members->currentState.activeScenes.end(), scene);
				_members->currentState.activeScenes.erase(it, _members->currentState.activeScenes.end());
			}
			{
				auto it = std::remove(_members->currentState.scenes.begin(), _members->currentState.scenes.end(), scene);
				_members->currentState.scenes.erase(it, _members->currentState.scenes.end());
			}
			{
				Render* render = findRenderForScene(sceneName);
				auto it = std::remove(_members->currentState.activeRenderers.begin(), _members->currentState.activeRenderers.end(), render);
				_members->currentState.activeRenderers.erase(it, _members->currentState.activeRenderers.end());
			}
			_members->currentState.rendererMap.erase(sceneName);
		}
	}

	const std::vector<Render*>& SceneManager::getActiveScenesRenderer() const
	{
		return _members->currentState.activeRenderers;
	}

	const std::vector<Scene*>& SceneManager::getActiveScenes() const
	{
		return _members->currentState.activeScenes;
	}

	const std::vector<Scene*>& SceneManager::getScenes() const
	{
		return _members->currentState.scenes;
	}

	const SceneManagerState& SceneManager::getCurrentState() const
	{
		return _members->currentState;
	}

	void SceneManager::update()
	{
		removeDeletedScenes();
	}

	void SceneManager::removeDeletedScenes()
	{
		if(!_members->sceneContainer.empty())
		{
			for(Scene* scene : _members->scenesToRemove)
			{
				auto it = std::remove_if(_members->sceneContainer.begin(), _members->sceneContainer.end(),
										 PointerEqualTo<Scene>(scene));
				_members->sceneContainer.erase(it, _members->sceneContainer.end());
			}
			_members->scenesToRemove.clear();
		}
	}

	void SceneManager::whenSceneActivationChanged()
	{
		_members->currentState.activeScenes.clear();
		_members->currentState.activeRenderers.clear();
		for(Scene* scene : _members->currentState.scenes)
		{
			if(scene->isActive())
			{
				_members->currentState.activeScenes.push_back(scene);
				Render* render = findRenderForScene(scene->getName());
				_members->currentState.activeRenderers.push_back(render);
			}
		}
	}

	void SceneManager::whenScenePriorityChanged()
	{
		std::map<Render*, int32_t> prioirtyMap;
		for(Scene* scene : _members->currentState.activeScenes)
		{
			Render* render = findRenderForScene(scene->getName());
			prioirtyMap[render] = scene->getRenderPriority();
		}
		std::sort(_members->currentState.activeRenderers.begin(), _members->currentState.activeRenderers.end(),
				  [&prioirtyMap](Render* a, Render* b)->bool 
		{
			return prioirtyMap[a] > prioirtyMap[b];
		});
	}

}