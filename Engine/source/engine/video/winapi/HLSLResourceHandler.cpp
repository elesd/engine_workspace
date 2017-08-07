#include <stdafx.h>
#include <engine/video/winapi/HLSLResourceHandler.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/ShaderResourceDescription.h>

#include <engine/video/winapi/HLSLResourceBinding.h>
#include <engine/video/winapi/ConstantBufferObject.h>
#include <engine/video/winapi/DriverImpl.h>

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

		void HLSLResourceHandler::commitValue(const ShaderResourceDescription& desc, const ConstantBufferObject& buffer)
		{
			DriverImpl* winapiDrv = static_cast<DriverImpl*>(getDriver());
			const HLSLResourceBinding* binding = static_cast<const HLSLResourceBinding*>(desc.getResourceBinding());

			for(ShaderType type : binding->getShaderTypes())
			{
				winapiDrv->setConstantBufferObject(type, binding->getBufferId(), &buffer);
			}
		}

		void HLSLResourceHandler::commitValueImpl(const ShaderResourceDescription& desc, float value)
		{
			ConstantBufferObject tempBuffer = createConstantBufferObject(value, getDriver());
			commitValue(desc, tempBuffer);
		}

		void HLSLResourceHandler::commitValueImpl(const ShaderResourceDescription& desc, const glm::vec2& value)
		{
			ConstantBufferObject tempBuffer = createConstantBufferObject(value, getDriver());
			commitValue(desc, tempBuffer);
		}

		void HLSLResourceHandler::commitValueImpl(const ShaderResourceDescription& desc, const glm::vec3& value)
		{
			ConstantBufferObject tempBuffer = createConstantBufferObject(value, getDriver());
			commitValue(desc, tempBuffer);
		}

		void HLSLResourceHandler::commitValueImpl(const ShaderResourceDescription& desc, const glm::vec4& value)
		{
			ConstantBufferObject tempBuffer = createConstantBufferObject(value, getDriver());
			commitValue(desc, tempBuffer);
		}

		void HLSLResourceHandler::commitValueImpl(const ShaderResourceDescription& desc, const glm::mat3& value)
		{
			ConstantBufferObject tempBuffer = createConstantBufferObject(value, getDriver());
			commitValue(desc, tempBuffer);
		}

		void HLSLResourceHandler::commitValueImpl(const ShaderResourceDescription& desc, const glm::mat4& value)
		{
			ConstantBufferObject tempBuffer = createConstantBufferObject(value, getDriver());
			commitValue(desc, tempBuffer);
		}

		std::unique_ptr<ShaderResourceHandler> HLSLResourceHandler::cloneImpl() const
		{
			return std::make_unique<HLSLResourceHandler>(static_cast<DriverImpl*>(getDriver()));
		}


	}
}