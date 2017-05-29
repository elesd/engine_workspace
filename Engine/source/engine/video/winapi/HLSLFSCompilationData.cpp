#include <stdafx.h>
#include <engine/video/winapi/HLSLFSCompilationData.h>
///////////////////////////////////////////////////////////////////////////////

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
			ID3D11InputLayout* layout = nullptr;
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
				if(_members->layout)
				{
					_members->layout->Release();
				}
			}
			delete _members;
		}

		void HLSLFSCompilationData::setOk(ID3D10Blob* compiledCode, ID3D11PixelShader* shader, ID3D11InputLayout* layout)
		{
			ShaderCompilationData::setOk();
			_members->compiledCode = compiledCode;
			_members->shader = shader;
			_members->layout = layout;
		}

		ID3D11PixelShader* HLSLFSCompilationData::getShaderInterface() const
		{
			return _members->shader;
		}

		ID3D11InputLayout* HLSLFSCompilationData::getLayoutInterface() const
		{
			return _members->layout;
		}
	}
}