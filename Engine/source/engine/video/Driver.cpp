#include <stdafx.h>

#include <engine/video/Driver.h>
///////////////////////////////////////////////////////////////////////////////
#include <engine/exceptions/LogicalErrors.h>

#include <engine/render/RenderContext.h>
#include <engine/render/Effect.h>

#include <engine/video/RenderTarget.h>
namespace
{
	enum class InitDriverParameterError
	{
		Ok,
		WrongSampleCount
	};

	std::string InitDriverParameterErrorToString(InitDriverParameterError e)
	{
		switch(e)
		{
			case InitDriverParameterError::Ok: return "Ok";
			case InitDriverParameterError::WrongSampleCount: return "WrongSampleCount";
			default: return "Unknown error";
		}
	} 

	InitDriverParameterError checkDriverInitParameters(const engine::DriverInitParameters &params)
	{
		if(params.sampleCount == 0)
			return InitDriverParameterError::WrongSampleCount;
		
		return InitDriverParameterError::Ok;
	}

}

namespace engine
{


	Driver::Driver()
	{

	}

	Driver::~Driver()
	{
	}

	void Driver::init(const DriverInitParameters &params, Window *window)
	{

		InitDriverParameterError checkResult = checkDriverInitParameters(params);
		if(checkResult != InitDriverParameterError::Ok)
		{
			std::string str = InitDriverParameterErrorToString(checkResult);
			throw InitializationError(str);
		}
		initImpl(params, window);
	}

	void Driver::draw(const VertexBuffer* verticies, const IndexBufferBase* indicies)
	{
		drawImpl(verticies, indicies);
	}

	void Driver::setViewPort(int32_t topX, int32_t topY, int32_t width, int32_t height)
	{
		setViewPortImpl(topX, topY, width, height);
	 }

	std::unique_ptr<RenderTarget> Driver::createRenderTarget(Texture* texture)
	{
		return createRenderTargetImpl(texture);
	}

	void Driver::compileShader(Shader *shader, const std::string& techniqueName, const ShaderCompileOptions& options)
	{
		compileShaderImpl(shader, techniqueName, options);
	}

	void Driver::setRenderTarget(RenderTarget* renderTarget)
	{
		setRenderTargetImpl(renderTarget);
	}

	void Driver::setShader(Shader* shader, const std::string& techniqueName)
	{
		setShaderImpl(shader, techniqueName);
	}

	void Driver::swapBuffer()
	{
		swapBufferImpl();
	}
}