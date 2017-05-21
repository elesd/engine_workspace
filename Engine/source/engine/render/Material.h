#pragma once

#include <engine/constraints/NonCopyable.h>

namespace engine
{
	class Shader;
	class Material 
		: private NonCopyable
	{
	public:
		Material(const std::string& name);
		~Material();
		Material(Material&&);
		Material& operator=(Material&&);
		void SetVertexShader(const Shader&);
		void SetFragmentShader(const Shader&);

		const Shader& getVertexShader();
		const Shader& getFragmentShader();

	private:
		struct MaterialPrivate* _members = nullptr;
	};
}