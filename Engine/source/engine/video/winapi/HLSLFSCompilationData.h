#pragma once

#include <engine/video/ShaderCompilationData.h>

struct ID3D10Blob;
struct ID3D11PixelShader;
namespace engine
{
	namespace winapi
	{
		class HLSLFSCompilationData : public ShaderCompilationData
		{
		public:
			HLSLFSCompilationData(const ShaderCompileOptions& options);
			~HLSLFSCompilationData() override;

			void setOk(ID3D10Blob* compiledCode, ID3D11PixelShader* shader);
			ID3D11PixelShader* getShaderInterface() const;
		private:
			struct HLSLFSCompilationDataPrivate* _members = nullptr;
		};
	}
}