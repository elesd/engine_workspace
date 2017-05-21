#include <stdafx.h>

#include <engine/video/Driver.h>
///////////////////////////////////////////////////////////////////////////////
#include <engine/exceptions/LogicalErrors.h>

#include <engine/render/RenderContext.h>
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
	struct DriverPrivate
	{
		RenderContext* renderContext = nullptr;
	};

	Driver::Driver()
		: _members(new DriverPrivate())
	{

	}

	Driver::~Driver()
	{
		delete _members;
		_members = nullptr;
	}

	void Driver::init(RenderContext *renderContext, const DriverInitParameters &params, Window *window)
	{
		_members->renderContext = renderContext;

		InitDriverParameterError checkResult = checkDriverInitParameters(params);
		if(checkResult != InitDriverParameterError::Ok)
		{
			std::string str = InitDriverParameterErrorToString(checkResult);
			throw InitializationError(str);
		}
		initImpl(params, window);
	}

	void Driver::draw(const VertexBuffer* verticies, const IndexBuffer* indicies)
	{
		drawImpl(verticies, indicies);
	}

	void Driver::setViewPort(int32_t topX, int32_t topY, int32_t width, int32_t height)
	{
		setViewPortImpl(topX, topY, width, height);
	 }

	RenderContext* Driver::getRenderContext()
	{
		return _members->renderContext;
	}

	void Driver::setRenderTarget(RenderTarget* renderTarget)
	{
		if(getRenderContext()->getCurrentRenderTarget() != renderTarget)
		{
			setRenderTargetImpl(renderTarget);
			getRenderContext()->setCurrentRenderTarget(renderTarget);
		}
	}

	void Driver::setMaterial(Material* material)
	{
		if(getRenderContext()->getCurrentMaterial() != material)
		{
			setMaterialImpl(material);
			getRenderContext()->setCurrentMaterial(material);
		}
	}
}