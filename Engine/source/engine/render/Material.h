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

		void setVertexShader(std::unique_ptr<Shader>&& shader, const std::string& techniqueName);
		void setFragmentShader(std::unique_ptr<Shader>&&, const std::string& techniqueName);

		const Shader* getVertexShader() const;
		const Shader* getFragmentShader() const;

		Shader* getVertexShader();
		Shader* getFragmentShader();

		void setVertexShaderTechniqueName(const std::string&);
		void setFragmentShaderTechniqueName(const std::string&);
		const std::string& getVertexShaderTechniqueName() const;
		const std::string& getFragmentShaderTechniqueName() const;

	private:
		struct MaterialPrivate* _members = nullptr;
	};
}