#include <stdafx.h>
#include <engine/video/winapi/HLSLFSCompilationData.h>
///////////////////////////////////////////////////////////////////////////////

#if ENGINE_USE_WINAPI

#include <d3d11.h>
#include <D3Dcompiler.h>

namespace engine
{
	namespace winapi
	{

		struct HLSLFSCompilationDataPrivate
		{
			ID3DBlob* compiledCode = nullptr;
			ID3D11PixelShader* shader = nullptr;
		};

		HLSLFSCompilationData::HLSLFSCompilationData(const ShaderCompileOptions& options)
			: ShaderCompilationData(options)
			, _members(new HLSLFSCompilationDataPrivate())
		{
		}

		HLSLFSCompilationData::~HLSLFSCompilationData()
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

		void HLSLFSCompilationData::setOk(ID3D10Blob* compiledCode, ID3D11PixelShader* shader)
		{
			ShaderCompilationData::setOk();
			_members->compiledCode = compiledCode;
			_members->shader = shader;
		}

		ID3D11PixelShader* HLSLFSCompilationData::getShaderInterface() const
		{
			return _members->shader;
		}
	}
}

#else

#include <engine/video/winapi/empty/HLSLFSCompilationData.cpp>


#endif