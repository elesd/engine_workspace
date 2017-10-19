#include <stdafx.h>
#include <engine/servicies/SynchronizerService.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/entityFramework/Component.h>
#include <engine/entityFramework/Entity.h>
#include <engine/entityFramework/VisualComponent.h>

#include <engine/libraries/MaterialInstance.h>
#include <engine/libraries/MaterialLibrary.h>

#include <engine/scene/Scene.h>
#include <engine/scene/SceneManager.h>

#include <engine/video/Material.h>
namespace engine
{
	struct SynchronizerServicePrivate
	{
		MaterialLibrary* materialLibrary = nullptr;
		SceneManager* sceneManager = nullptr;
	};

	SynchronizerService::SynchronizerService()
		: _members(new SynchronizerServicePrivate())
	{

	}

	SynchronizerService::~SynchronizerService()
	{
		delete _members;
		_members = nullptr;
	}

	void SynchronizerService::setupSceneManager(SceneManager* sceneManager)
	{
		ASSERT(_members->sceneManager == nullptr);
		_members->sceneManager = sceneManager;
	}

	void SynchronizerService::setupMaterialLibrary(MaterialLibrary* materialLibrary)
	{
		ASSERT(_members->materialLibrary == nullptr);
		_members->materialLibrary = materialLibrary;
	}

	void SynchronizerService::sync()
	{
		syncActiceScenes();
	}

	void SynchronizerService::syncActiceScenes()
	{
		std::vector<Scene*> activeScenes = _members->sceneManager->getActiveScenes();
		for(Scene* scene : activeScenes)
		{
			syncScene(scene);
		}
	}

	void SynchronizerService::syncScene(Scene* scene)
	{
		std::vector<Entity*> entities = scene->getEntities();
		for(Entity* entity : entities)
		{
			syncMaterial(entity);
		}
	}

	void SynchronizerService::syncMaterial(Entity* entity)
	{
		std::vector<VisualComponent*> visualComponents = entity->getVisualComponents();
		for(VisualComponent* component : visualComponents)
		{
			std::vector<MaterialInstance*> materials = component->collectMaterials();
			for(MaterialInstance* materialInstance : materials)
			{
				Material* material = _members->materialLibrary->getMaterialOrigin(materialInstance->getMaterialName());
				material->sync(materialInstance);
			}
		}
	}

}