#pragma once

#include <engine/video/ShaderResourceTraits.h>
#include <engine/constraints/NonCopyable.h>
#include <engine/video/ShaderResourceDescription.h>
#include <engine/video/ShaderResourceHandler.h>

namespace engine
{
	class ShaderResourceHandler;

	template<GPUMemberType Type>
	class ShaderResource final
		: private NonCopyable
	{
	public:
		ShaderResource() = default;
		ShaderResource(ShaderResourceHandler* resourceHandler, const ShaderResourceDescription& description);
		ShaderResource(ShaderResource&& o);
		~ShaderResource();

		ShaderResource& operator=(ShaderResource&& o);

		const typename ShaderResourceTraits<Type>::ValueType& getValue() const;

		void setValue(const typename ShaderResourceTraits<Type>::ValueType& value);

		void commitChanges();
	private:
		ShaderResourceHandler* _resourceHandler = nullptr;
		bool _changed = true;
		ShaderResourceDescription _description;
		typename ShaderResourceTraits<Type>::ValueType _value;
	};
}

#include <engine/video/ShaderResource.hpp>