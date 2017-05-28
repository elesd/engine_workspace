#pragma once

#include <engine/video/ShaderCompilationData.h>

struct ID3D10Blob;
struct ID3D11VertexShader;
namespace engine
{
	namespace winapi
	{
		class HLSLVSCompilationData : public ShaderCompilationData
		{
		public:
			HLSLVSCompilationData(const ShaderCompileOptions& options);
			~HLSLVSCompilationData() override;

			void setOk(ID3D10Blob* compiledCode, ID3D11VertexShader* shader);
			ID3D11VertexShader* getShaderInterface() const;
		private:
			struct HLSLVSCompilationDataPrivate* _members = nullptr;
		};
	}
}