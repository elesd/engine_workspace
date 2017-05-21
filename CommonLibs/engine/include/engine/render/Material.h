#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/PIMPLMoveable.h>

namespace engine
{
	class Shader;
	class Material : private NonCopyable
		, public PIMPLMoveable<Material>

	{
	public:
		Material(const std::string& name);
		~Material();
		void SetVertexShader(const Shader&);
		void SetFragmentShader(const Shader&);

		const Shader& getVertexShader();
		const Shader& getFragmentShader();

	private:
		struct MaterialPrivate* _members = nullptr;
	};
}