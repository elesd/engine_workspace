#pragma once

#include <engine/video/BufferDesc.h>
#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>


namespace engine
{
	class AttributeFormat;
	class BufferContext;
	class Effect;
	class EffectComperator;
	class IndexBufferBase;
	class Material;
	class RenderContext;
	class RenderTarget;
	class Shader;
	class ShaderCompileOptions;
	class GlobalShaderResourceStorage;
	class ShaderResourceStorage;
	class ShaderResourceDescription;
	class ShaderResourceHandler;
	class ShaderResourceBinding;
	class Texture;
	class VertexBuffer;
	class WindowManager;
	class Window;

	enum class DriverVersion
	{
		DirectX11,
		OpenGL_Core_3_2,
		OpenGL_Core_3_3,
		OpenGL_Core_4_0,
		OpenGL_Core_4_1,
		OpenGL_Core_4_2,
		OpenGL_Core_4_3,
		OpenGL_Core_4_4,
		OpenGL_Core_4_5,
		OpenGL_ES_2_0,
		OpenGL_ES_3_0,
	};
	struct DeviceParameters
	{
		DriverVersion version;
	};

	/**Initialization parameters for the driver*/
	struct DriverInitParameters
	{
		/**Buffer descripition of the main buffer*/
		BufferDesc description;
		/**Sample count of the driver*/
		int32_t sampleCount;
	};


	/**
	* Video driver interface implementation.
	* All the graphical instructions will be executed via this class implementation.
	*/
	class Driver
		: private NonCopyable
		, private NonMoveable
	{
		friend class WindowManager;

	protected:
		/**Simple constructor*/
		Driver();
	public:
		/**Virtual destructor*/
		virtual ~Driver();
		void initDevice(const DeviceParameters& params);

		void setWindow(Window *window);

		/**Init function*/
		void init(const DriverInitParameters& params);

		void draw(BufferContext *bufferContext);
		void setRenderTarget(RenderTarget* renderTarget);
		void setViewPort(int32_t x, int32_t y, int32_t width, int32_t height);
		std::unique_ptr<RenderTarget> createRenderTarget(std::unique_ptr<Texture>&& texture);
		void compileShader(Shader *shader, const std::string& techniqueName, const ShaderCompileOptions& options, const AttributeFormat& format);
		void compileEffect(Effect* effect);
		std::unique_ptr<ShaderResourceBinding> bindResource(const ShaderResourceDescription& desc, Effect* effect);
		void setEffect(Effect *effect, const EffectComperator& comperator);
		void setShader(Shader* shader, const std::string& techniqueName);
		void swapBuffer();
		const DriverInitParameters& getParameters() const;
		const DeviceParameters& getDeviceParameters() const;

		bool checkDeviceSetup();
		std::unique_ptr<ShaderResourceStorage> createResourceStorage(const std::vector<ShaderResourceDescription>& description, GlobalShaderResourceStorage* parent = nullptr);

		std::unique_ptr<ShaderResourceHandler> createShaderResourceHandler();

		std::pair<float, float> getViewportRange() const;
	protected:
		Window* getWindow() const;

	private:
		virtual void initDeviceImpl(const DeviceParameters& params) = 0;
		/**Platform specific init implementation*/
		virtual void initImpl(const DriverInitParameters& params) = 0;
		virtual void compileShaderImpl(Shader *shader, const std::string& techniqueName, const ShaderCompileOptions& options, const AttributeFormat& format) = 0;
		virtual void compileEffectImpl(Effect* effect) = 0;
		virtual void drawImpl(BufferContext *bufferContext) = 0;
		virtual void setEffectImpl(Effect* effect) = 0;
		virtual void setShaderImpl(Shader* shader, const std::string& techniqueName) = 0;
		virtual std::unique_ptr<RenderTarget> createRenderTargetImpl(std::unique_ptr<Texture>&& texture) = 0;

		virtual void setViewPortImpl(int32_t x, int32_t y, int32_t width, int32_t height) = 0;
		virtual void setRenderTargetImpl(RenderTarget* renderTarget) = 0;
		virtual void swapBufferImpl() = 0;
		virtual bool checkDeviceSetupImpl() = 0;
		virtual std::unique_ptr<ShaderResourceHandler> createShaderResourceHandlerImpl() = 0;
		virtual std::unique_ptr<ShaderResourceBinding> bindResourceImpl(const ShaderResourceDescription& desc, Effect* effect) = 0;
		virtual std::pair<float, float> getViewportRangeImpl() const = 0;

	private:
		struct DriverPrivate* _members = nullptr;
	};
}