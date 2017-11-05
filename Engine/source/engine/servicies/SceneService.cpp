#include <stdafx.h>
#include <engine/servicies/SceneService.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/scene/SceneManager.h>
#include <engine/scene/Scene.h>

namespace engine
{
	struct SceneServicePrivate
	{
		SceneManager* sceneManager = nullptr;
		RenderContext* renderContext = nullptr;
		explicit SceneServicePrivate(SceneManager* sceneManager, RenderContext* renderContext)
			: sceneManager(sceneManager)
			, renderContext(renderContext)
		{ }
	};

	SceneService::SceneService(SceneManager* sceneManager, RenderContext* renderContext)
		: _members(new SceneServicePrivate(sceneManager, renderContext))
	{

	}

	SceneService::~SceneService()
	{
		delete _members;
		_members = nullptr;
	}

	SceneProxy* SceneService::createScene(const std::string& sceneName, const std::string& rendererName, std::unique_ptr<ComponentRegister>&& componentRegister)
	{
		Scene* scene = _members->sceneManager->createScene(sceneName, _members->renderContext, rendererName, std::move(componentRegister));
		return scene->getProxy();
	}

	SceneProxy* SceneService::findScene(const std::string& sceneName) const
	{
		Scene* scene = _members->sceneManager->findScene(sceneName);
		return scene->getProxy();
	}

}