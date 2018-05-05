#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/video/ShaderResourceBinding.h>
#include <engine/video/ShaderResourceDescription.h>
#include <engine/video/ShaderResourceHandler.h>
#include <engine/video/GPUTypes.h>

#include <memory>

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

		const typename GPUMemberTypeTraits<Type>::ValueType& getValue() const;

		void setValue(const typename GPUMemberTypeTraits<Type>::ValueType& value);

		void bind(std::unique_ptr<ShaderResourceBinding>&& binding);
		bool isBound() const;
		ShaderResourceBinding* getBinding();

		const ShaderResourceDescription& getDescription() const;

		void commitChanges();
	private:
		ShaderResourceHandler* _resourceHandler = nullptr;
		bool _changed = true;
		typename GPUMemberTypeTraits<Type>::ValueType _value;
		ShaderResourceDescription _description;
		std::unique_ptr<ShaderResourceBinding> _binding;
	};
}

#include <engine/video/ShaderResource.hpp>
