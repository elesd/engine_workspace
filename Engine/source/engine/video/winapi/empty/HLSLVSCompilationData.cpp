#include <stdafx.h>
#include <engine/video/winapi/HLSLVSCompilationData.h>
///////////////////////////////////////////////////////////////////////////////


namespace engine
{
	namespace winapi
	{

	

		HLSLVSCompilationData::HLSLVSCompilationData(const ShaderCompileOptions& options)
			: ShaderCompilationData(options)
		{INACTIVE_MODULE_ERROR(); }

		HLSLVSCompilationData::~HLSLVSCompilationData()
		{
			INACTIVE_MODULE_ERROR();
		}

		void HLSLVSCompilationData::setOk(ID3D10Blob* compiledCode, ID3D11VertexShader* shader, ID3D11InputLayout* layout)
		{
			INACTIVE_MODULE_ERROR();
		}

		ID3D11VertexShader* HLSLVSCompilationData::getShaderInterface() const
		{
			INACTIVE_MODULE_ERROR();
			return nullptr;
		}

		ID3D11InputLayout* HLSLVSCompilationData::getLayoutInterface() const
		{
			INACTIVE_MODULE_ERROR();
			return nullptr;
		}


	}
}