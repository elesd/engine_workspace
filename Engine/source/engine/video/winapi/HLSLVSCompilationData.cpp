#include <stdafx.h>
#include <engine/video/winapi/HLSLVSCompilationData.h>
///////////////////////////////////////////////////////////////////////////////

#include <d3d11.h>
#include <D3Dcompiler.h>

namespace engine
{
	namespace winapi
	{

		struct HLSLVSCompilationDataPrivate
		{
			ID3DBlob* compiledCode = nullptr;
			ID3D11VertexShader* shader = nullptr;
		};

		HLSLVSCompilationData::HLSLVSCompilationData(const ShaderCompileOptions& options)
			: ShaderCompilationData(options)
			, _members(new HLSLVSCompilationDataPrivate())
		{ }

		HLSLVSCompilationData::~HLSLVSCompilationData()
		{
			if(_members)
			{
				if(_members->compiledCode)
				{
					_members->compiledCode->Release();
				}
				if(_members->shader)
				{
					_members->shader->Release();
				}
			}
			delete _members;
		}

		void HLSLVSCompilationData::setOk(ID3D10Blob* compiledCode, ID3D11VertexShader* shader)
		{
			ShaderCompilationData::setOk();
			_members->compiledCode = compiledCode;
			_members->shader = shader;
		}

		ID3D11VertexShader* HLSLVSCompilationData::getShaderInterface() const
		{
			return _members->shader;
		}

	}
}