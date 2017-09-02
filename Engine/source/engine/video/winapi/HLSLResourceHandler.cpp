#include <stdafx.h>
#include <engine/video/winapi/HLSLResourceHandler.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/ShaderResourceDescription.h>

#include <engine/video/winapi/HLSLResourceBinding.h>
#include <engine/video/winapi/ConstantBufferObject.h>
#include <engine/video/winapi/DriverImpl.h>
#if ENGINE_USE_WINAPI
namespace
{
	template<class T>
	engine::winapi::ConstantBufferObject createConstantBufferObject(const T& value, engine::Driver* driver)
	{
		engine::winapi::ConstantBufferObject tempBuffer(sizeof(T), driver);
		tempBuffer.bind();
		std::vector<char> data(sizeof(T));
		std::memcpy(data.data(), &value, data.size());
		tempBuffer.setData(data.data(), sizeof(value));
		tempBuffer.unbind();
		return tempBuffer;
	}
}

namespace engine
{
	namespace winapi
	{

		HLSLResourceHandler::HLSLResourceHandler(DriverImpl* driver)
			: ShaderResourceHandler(driver)
		{
		}

		void HLSLResourceHandler::commitValue(const ShaderResourceBinding* binding, const ConstantBufferObject& buffer)
		{
			DriverImpl* winapiDrv = static_cast<DriverImpl*>(getDriver());
			const HLSLResourceBinding* winapiBinding = static_cast<const HLSLResourceBinding*>(binding);

			for(ShaderType type : winapiBinding->getShaderTypes())
			{
				winapiDrv->setConstantBufferObject(type, winapiBinding->getBufferId(), &buffer);
			}
		}

		void HLSLResourceHandler::commitValueImpl(const ShaderResourceDescription& desc, const ShaderResourceBinding* binding, float value)
		{
			ConstantBufferObject tempBuffer = createConstantBufferObject(value, getDriver());
			commitValue(binding, tempBuffer);
		}

		void HLSLResourceHandler::commitValueImpl(const ShaderResourceDescription& desc, const ShaderResourceBinding* binding, const glm::vec2& value)
		{
			ConstantBufferObject tempBuffer = createConstantBufferObject(value, getDriver());
			commitValue(binding, tempBuffer);
		}

		void HLSLResourceHandler::commitValueImpl(const ShaderResourceDescription& desc, const ShaderResourceBinding* binding, const glm::vec3& value)
		{
			ConstantBufferObject tempBuffer = createConstantBufferObject(value, getDriver());
			commitValue(binding, tempBuffer);
		}

		void HLSLResourceHandler::commitValueImpl(const ShaderResourceDescription& desc, const ShaderResourceBinding* binding, const glm::vec4& value)
		{
			ConstantBufferObject tempBuffer = createConstantBufferObject(value, getDriver());
			commitValue(binding, tempBuffer);
		}

		void HLSLResourceHandler::commitValueImpl(const ShaderResourceDescription& desc, const ShaderResourceBinding* binding, const glm::mat3& value)
		{
			ConstantBufferObject tempBuffer = createConstantBufferObject(glm::transpose(value), getDriver());
			commitValue(binding, tempBuffer);
		}

		void HLSLResourceHandler::commitValueImpl(const ShaderResourceDescription& desc, const ShaderResourceBinding* binding, const glm::mat4& value)
		{
			ConstantBufferObject tempBuffer = createConstantBufferObject(glm::transpose(value), getDriver());
			commitValue(binding, tempBuffer);
		}

	}
}
#endif
