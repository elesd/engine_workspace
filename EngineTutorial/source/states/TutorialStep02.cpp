#include <stdafx.h>
#include <states/TutorialStep02.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/Context.h>

#include <engine/app/Application.h>

#include <engine/entityFramework/Entity.h>
#include <engine/entityFramework/CameraComponent.h>
#include <engine/entityFramework/PerspProjectionComponent.h>
#include <engine/entityFramework/MeshComponent.h>

#include <engine/events/EventManager.h>
#include <engine/events/Keyboard.h>

#include <engine/fileSystem/FilePath.h>

#include <engine/libraries/ShaderLibraryLable.h>

#include <engine/render/RenderContext.h>
#include <engine/render/Render.h>
#include <engine/render/Mesh.h>

#include <engine/servicies/LibraryService.h>
#include <engine/libraries/ShaderInstance.h>

#include <engine/scene/Scene.h>
#include <engine/scene/SceneManager.h>

#include <engine/video/AttributeFormat.h>
#include <engine/video/BufferContext.h>
#include <engine/video/Effect.h>
#include <engine/video/EffectCompiler.h>
#include <engine/video/EffectDescription.h>
#include <engine/video/GPUTypes.h>
#include <engine/video/IndexBuffer.h>
#include <engine/video/GlobalShaderResourceStorage.h>
#include <engine/video/Material.h>
#include <engine/video/MaterialDescription.h>
#include <engine/video/Shader.h>
#include <engine/video/ShaderCompileOptions.h>
#include <engine/video/MaterialResourceHandler.h>
#include <engine/video/ShaderResourceDescription.h> 
#include <engine/video/ShaderResourceStorage.h>
#include <engine/video/ShaderResourceBindingData.h>
#include <engine/video/VertexBuffer.h>

#include <engine/view/Console.h>
#include <engine/view/Window.h>

#include <RenderDefinitions.h>
#include <componentRegisters/SolidComponentRegister.h>

using namespace engine;

namespace states
{
	struct TutorialStep02Private
	{
		RenderContext* renderContext = nullptr;
		Scene* scene = nullptr;
		Render* render = nullptr;
		renderPasses::OnlySloid::PipelineRenderer* renderPipeline = nullptr;

		std::unique_ptr<Mesh> triangle;

		glm::vec4 instanceColor;
		explicit TutorialStep02Private(Window* window)
			: renderContext(window->getRenderContext())
			, instanceColor(0.5f, 0.0f, 0.0f, 0.0f)
		{ }
	};

	TutorialStep02::TutorialStep02(Window *window)
		: StateBase("TutorialStep02", window)
		, _members(new TutorialStep02Private(window))
	{

	}

	TutorialStep02::~TutorialStep02()
	{
		delete _members;
		_members = nullptr;
	}

	void TutorialStep02::initState()
	{
		initRender();
		initShaders();
		initTriangle();
		//_members->renderPipeline->getRenderPass(renderPasses::TutorialStep02::Passes::Solid)->addObject(_members->triangle.get());
		createConnections();
		loadScene();
	}

	void TutorialStep02::destroyState()
	{

	}

	void TutorialStep02::resumeState()
	{

	}

	void TutorialStep02::pauseState()
	{

	}

	void TutorialStep02::updateState()
	{
	}

	void TutorialStep02::initRender()
	{
		std::unique_ptr<PipelineRendererBase> renderTutorialStep02 = renderPasses::OnlySloid::createRenderer(getWindow()->getRenderContext());
		_members->render = _members->renderContext->createRender("TutorialStep02", std::move(renderTutorialStep02));
		_members->renderPipeline = _members->render->getPipeline<renderPasses::OnlySloid::PipelineRenderer>();
	}

	void TutorialStep02::initTriangle()
	{
		_members->triangle = std::make_unique<Mesh>("triangle");
		std::unique_ptr<BufferContext> bufferContext = _members->renderContext->createBufferContext();
		std::unique_ptr<Material> material = loadMaterial();
		loadTriangleVerticies(material.get(), bufferContext.get());
		loadTriangleIndicies(bufferContext.get());
		bufferContext->finalize();
		_members->triangle->load(std::move(bufferContext), std::move(material));
	}

	void TutorialStep02::initShaders()
	{
		std::string vsPath;
		std::string fsPath;
		std::string vsMain;
		std::string fsMain;
#if TUTORIAL_USE_WINAPI
	
		vsPath = "shaders/hlsl/Tutorial02.hlsl";
		vsMain = "VShader";
		fsPath = "shaders/hlsl/Tutorial02.hlsl";
		fsMain = "PShader";
	
#else
		vsPath = "shaders/glsl/Tutorial02_vs.glsl";
		vsMain = "main";
		fsPath = "shaders/glsl/Tutorial02_fs.glsl";
		fsMain = "main";
#endif
		Context::libraryService()->addShader(ShaderLibraryLabel("tutorial02", FilePath(vsPath), ShaderType::VertexShader, vsMain));
		Context::libraryService()->addShader(ShaderLibraryLabel("tutorial02", FilePath(fsPath), ShaderType::FragmentShader, fsMain));
	}

	void TutorialStep02::loadScene()
	{
		std::unique_ptr<SolidComponentRegister> componentRegister(new SolidComponentRegister());
		_members->scene = Context::application()->getSceneManager()->createScene("TutorialStep02", _members->renderContext, "TutorialStep02", std::move(componentRegister));
	/*	{
			std::unique_ptr<Entity> camera(new Entity("Camera"));
			PerspectiveProjectionSettings settings(glm::radians(70.0f), 0.1f, 100.0f);
			std::unique_ptr<CameraComponent> cameraComponent(new CameraComponent(_members->window, settings, glm::vec3(0.0f)));
			camera->registerCameraComponent(std::move(cameraComponent));
			_members->scene->registerEntity(std::move(camera));
		}*/
		{
			std::unique_ptr<Entity> entity(new Entity("Triangle"));
			std::unique_ptr<MeshComponent> meshComponent(new MeshComponent(_members->triangle.get()));
			entity->registerVisualComponent(std::move(meshComponent));
			_members->scene->registerEntity(std::move(entity));
		}
	}

	std::vector<ShaderResourceDescription> TutorialStep02::createHLSLMaterialParameters() const
	{
		std::vector<ShaderResourceDescription> result;
		result.push_back(ShaderResourceDescription("instanceColor",
						 GPUMemberType::Vec4,
						 ShaderResourceBindingData(0, {ShaderType::VertexShader})));
		return result;
	}

	std::vector<ShaderResourceDescription> TutorialStep02::createGLSLMaterialParameters() const
	{
		std::vector<ShaderResourceDescription> result;
		result.push_back(ShaderResourceDescription("instanceColor",
														   GPUMemberType::Vec4,
														   ShaderResourceBindingData({ ShaderType::VertexShader })));
		return result;
	}

	std::vector<ShaderResourceDescription> TutorialStep02::createMaterialParameters() const
	{
#if TUTORIAL_USE_WINAPI
		return createHLSLMaterialParameters();
#else
		return createGLSLMaterialParameters();
#endif
	}


	std::unique_ptr<Material> TutorialStep02::loadMaterial()
	{
		AttributeFormat layout;
		layout.insertAttribute(GPUMemberType::Vec3, 0, "position");
		layout.insertAttribute(GPUMemberType::Vec4, 1, "color");
#if TUTORIAL_USE_WINAPI
		MaterialDescription description(ShaderVersion::HLSL_5_0);
#else
		MaterialDescription description(ShaderVersion::GLSL_330);
#endif
		description.setFragmentShaderName("tutorial02");
		description.setVertexShaderName("tutorial02");
		
		std::vector<ShaderResourceDescription> materialParameters = createMaterialParameters();
		for(const ShaderResourceDescription& materialParam : materialParameters)
		{
			description.getDefaultEffect().addParameter(materialParam);
		}

		description.getDefaultEffect().getOptions().addFlag(ShaderCompileFlag::Debug);
		description.setAttributeFormat(layout);

		std::unique_ptr<Material> result = std::make_unique<Material>("Simple", description, _members->renderContext);
		result->getResourceHandler()->setVec4("instanceColor", _members->instanceColor);
		return result;
	}

	void TutorialStep02::loadTriangleVerticies(Material* material, BufferContext* bufferContext)
	{
#if TUTORIAL_USE_WINAPI
		std::vector<float> data(
		{
			0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.45f, -0.5, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			-0.45f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		});
#else
		std::vector<float> data(
		{
			-1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		});
#endif
		
		bufferContext->setupVertexBuffer(material->getAttributeFormat(), data);
	}

	void TutorialStep02::loadTriangleIndicies(BufferContext* bufferContext)
	{
		std::vector<int32_t> data = 
		{
			0, 1, 2
		};
		bufferContext->setupIndexBuffer(PrimitiveType::Triangle, data);
	}

	void TutorialStep02::createConnections()
	{
		Keyboard* keyboard = getWindow()->getEventManager()->findEventSource<Keyboard>()[0];
		CONNECT_SIGNAL(keyboard, keyReleased, this, onKeyUp);
	}

	void TutorialStep02::onKeyUp(KeyboardButton button)
	{
		switch(button)
		{
			case KeyboardButton::Key_Up:
				_members->instanceColor.r = (std::min)(1.0f, _members->instanceColor.r + 0.1f);
				break;
			case KeyboardButton::Key_Down:
				_members->instanceColor.r = (std::max)(0.0f, _members->instanceColor.r - 0.1f);
				break;
		}		
		_members->triangle->getMaterial()->getResourceHandler()->setVec4("instanceColor", _members->instanceColor);
	}
}
