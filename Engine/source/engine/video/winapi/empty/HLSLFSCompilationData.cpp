#include <stdafx.h>
#include <engine/video/winapi/HLSLFSCompilationData.h>
///////////////////////////////////////////////////////////////////////////////

namespace engine
{
	namespace winapi
	{


		HLSLFSCompilationData::HLSLFSCompilationData(const ShaderCompileOptions& options)
			: ShaderCompilationData(options)
		{
			INACTIVE_MODULE_ERROR();
		}

		HLSLFSCompilationData::~HLSLFSCompilationData()
		{
			INACTIVE_MODULE_ERROR();
		}

		void HLSLFSCompilationData::setOk(ID3D10Blob* compiledCode, ID3D11PixelShader* shader)
		{
			INACTIVE_MODULE_ERROR();
		}

		ID3D11PixelShader* HLSLFSCompilationData::getShaderInterface() const
		{
			INACTIVE_MODULE_ERROR();
			return nullptr;
		}
	}
}