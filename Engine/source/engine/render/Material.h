#pragma once

#include <engine/constraints/NonCopyable.h>

namespace engine
{
	class Effect;
	class EffectCompiler;
	class Shader;
	class MaterialDescription;

	class Material
		: private NonCopyable
	{
	public:
		Material(const std::string& name, std::unique_ptr<EffectCompiler>&& effectCompiler, const MaterialDescription& description);
		~Material();
		Material(Material&&);
		Material& operator=(Material&&);

		const std::string& getMaterialName() const;

		void setCurrentEffect(const std::string& name);
		const std::string& getCurrentEffectName() const;
		Effect* getEffect() const;

	private:
		struct MaterialPrivate* _members = nullptr;
	};
}