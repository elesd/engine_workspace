#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

#include <engine/utils/GuardedObject.h>

namespace engine
{
	class Shader;

	enum class ShaderType;

	class ShaderInstance final
		: private NonCopyable
		, private NonMoveable
	{
		friend class ShaderLibrary;
		friend class Driver;
	private:
		ShaderInstance(const std::shared_ptr<Shader>& shaderOrigin);
	public:
		~ShaderInstance();
		bool operator==(const ShaderInstance& o) const;
		bool isInitialized() const;
		bool isCompiled(const std::string& technique);
		ShaderType getShaderType() const;
		const std::string& getMainFunctionName();
		bool isSame(const std::string& technique, const ShaderInstance& o) const;
		const std::string& getCode() const;
	private:
		GuardedObject<Shader*> lockShader();
		GuardedObject<const Shader*> lockShader() const;
	private:
		struct ShaderInstancePrivate* _members = nullptr;
	};
}