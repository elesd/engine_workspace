#include <stdafx.h>

#include <engine/video/Driver.h>
///////////////////////////////////////////////////////////////////////////////
#include <engine/exceptions/LogicalErrors.h>
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

	void Driver::draw(const VertexBuffer* verticies, const IndexBuffer* indicies)
	{
		drawImpl(verticies, indicies);
	}
}