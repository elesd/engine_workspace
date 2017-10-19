#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	class Entity;
	class MaterialLibrary;
	class Scene;
	class SceneManager;

	class SynchronizerService
		: private NonCopyable
		, private NonMoveable
	{
	public:
		SynchronizerService();
		~SynchronizerService();

		void setupSceneManager(SceneManager* sceneManager);
		void setupMaterialLibrary(MaterialLibrary* materialLibrary);

		void sync();
	private:
		void syncActiceScenes();
		void syncScene(Scene* scene);
		void syncMaterial(Entity* entity);
	private:
		struct SynchronizerServicePrivate* _members = nullptr;
	};
}