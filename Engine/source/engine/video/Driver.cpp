#include <stdafx.h>

#include <engine/video/Driver.h>
///////////////////////////////////////////////////////////////////////////////
#include <engine/exceptions/LogicalErrors.h>

#include <engine/render/RenderContext.h>

#include <engine/video/Effect.h>
#include <engine/video/EffectComperator.h>
#include <engine/video/EffectCompilationData.h>
#include <engine/video/RenderTarget.h>
#include <engine/video/ShaderResourceStorage.h>
#include <engine/video/ShaderResourceHandler.h>
#include <engine/video/ShaderResourceDescription.h>
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
		Window* window = nullptr;
		DriverInitParameters parameters;
		DeviceParameters deviceParameters;
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

	void Driver::initDevice(const DeviceParameters& params)
	{
		_members->deviceParameters = params;
		initDeviceImpl(params);
	}

	void Driver::setWindow(Window *window)
	{
		ASSERT(_members->window == nullptr);
		_members->window = window;
	}

	void Driver::init(const DriverInitParameters &params)
	{
		_members->parameters = params;
		InitDriverParameterError checkResult = checkDriverInitParameters(params);
		if(checkResult != InitDriverParameterError::Ok)
		{
			std::string str = InitDriverParameterErrorToString(checkResult);
			throw InitializationError(str);
		}
		initImpl(params);
	}

	void Driver::draw(BufferContext *bufferContext)
	{
		drawImpl(bufferContext);
	}

	void Driver::setViewPort(int32_t x, int32_t y, int32_t width, int32_t height)
	{
		setViewPortImpl(x, y, width, height);
	 }

	std::unique_ptr<RenderTarget> Driver::createRenderTarget(std::unique_ptr<Texture>&&  texture)
	{
		return createRenderTargetImpl(std::move(texture));
	}

	void Driver::compileShader(Shader *shader, const std::string& techniqueName, const ShaderCompileOptions& options, const AttributeFormat& format)
	{
		compileShaderImpl(shader, techniqueName, options, format);
	}

	void Driver::compileEffect(Effect* effect)
	{
		compileEffectImpl(effect);
	}

	void Driver::setRenderTarget(RenderTarget* renderTarget)
	{
		setRenderTargetImpl(renderTarget);
	}

	void Driver::setShader(Shader* shader, const std::string& techniqueName)
	{
		setShaderImpl(shader, techniqueName);
	}

	void Driver::setEffect(Effect *effect, const EffectComperator& effectComperator)
	{
		effect->getResources()->commitResources();
		if(effect->getCompilationData()->isSupportSeparatePrograms())
		{
			if(effectComperator.isChanged(EffectComperator::DifferenceType::VertexShader))
			{
				setShader(effect->getVertexShader(), effect->getName());
			}
			if(effectComperator.isChanged(EffectComperator::DifferenceType::FragmentShader))
			{
				setShader(effect->getFragmentShader(), effect->getName());
			}
		}
		else if(effectComperator.hasAnyChange())
		{
			setEffectImpl(effect);
		}
	}

	void Driver::swapBuffer()
	{
		swapBufferImpl();
	}

	const DriverInitParameters& Driver::getParameters() const
	{
		return _members->parameters;
	}
	const DeviceParameters& Driver::getDeviceParameters() const
	{
		return _members->deviceParameters;
	}

	bool Driver::checkDeviceSetup()
	{
		return checkDeviceSetupImpl();
	}

	std::unique_ptr<ShaderResourceStorage> Driver::createResourceStorage(const std::vector<ShaderResourceDescription>& description, ShaderResourceStorage* parent)
	{
		std::unique_ptr<ShaderResourceHandler> resourceHandler = createShaderResourceHandler();
		std::unique_ptr<ShaderResourceStorage> result = std::make_unique<ShaderResourceStorage>(std::move(resourceHandler), parent);
		for(const ShaderResourceDescription& desc : description)
		{
			result->addResource(desc);
		}
		return result;
	}

	std::unique_ptr<ShaderResourceHandler> Driver::createShaderResourceHandler()
	{
		return createShaderResourceHandlerImpl();
	}


	Window* Driver::getWindow() const
	{
		return _members->window;
	}

}