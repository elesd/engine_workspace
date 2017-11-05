#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	class ComponentRegister;
	class RenderContext;
	class SceneManager;
	class SceneProxy;

	class SceneService final
		: private NonCopyable
		, private NonMoveable
	{
	public:
		explicit SceneService(SceneManager* sceneManager, RenderContext* renderContext);
		~SceneService();

		SceneProxy* createScene(const std::string& sceneName, const std::string& rendererName, std::unique_ptr<ComponentRegister>&& componentRegister);
		SceneProxy* findScene(const std::string& sceneName) const;

	private:
		struct SceneServicePrivate* _members = nullptr;
	};
}