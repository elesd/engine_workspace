#include <stdafx.h>
#include <states/TutorialStep03.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/Context.h>

#include <engine/app/Application.h>

#include <engine/entityFramework/Entity.h>
#include <engine/entityFramework/CameraComponent.h>
#include <engine/entityFramework/PerspProjectionComponent.h>
#include <engine/entityFramework/MeshComponent.h>
#include <engine/entityFramework/TransformationComponent.h>

#include <engine/events/EventManager.h>
#include <engine/events/Keyboard.h>

#include <engine/fileSystem/FilePath.h>

#include <engine/libraries/ShaderLibraryLable.h>
#include <engine/libraries/ShaderInstance.h>

#include <engine/render/RenderContext.h>
#include <engine/render/Render.h>
#include <engine/render/Mesh.h>

#include <engine/servicies/LibraryService.h>

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
#include <engine/video/MaterialResourceHandler.h>
#include <engine/video/Shader.h>
#include <engine/video/ShaderCompileOptions.h>
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
	struct TutorialStep03Private
	{
		RenderContext* renderContext = nullptr;
		Scene* scene = nullptr;
		Entity* triangleEntity = nullptr;
		Render* render = nullptr;
		renderPasses::OnlySloid::PipelineRenderer* renderPipeline = nullptr;

		std::unique_ptr<Mesh> triangle;

		glm::vec4 instanceColor;
		explicit TutorialStep03Private(Window* window)
			: renderContext(window->getRenderContext())
			, instanceColor(0.5f, 0.0f, 0.0f, 0.0f)
		{ }
	};

	TutorialStep03::TutorialStep03(Window *window)
		: StateBase("TutorialStep03", window)
		, _members(new TutorialStep03Private(window))
	{

	}

	TutorialStep03::~TutorialStep03()
	{
		delete _members;
		_members = nullptr;
	}

	void TutorialStep03::initState()
	{
		initRender();
		initShaders();
		initTriangle();
		//_members->renderPipeline->getRenderPass(renderPasses::TutorialStep03::Passes::Solid)->addObject(_members->triangle.get());
		createConnections();
		loadScene();
	}

	void TutorialStep03::destroyState()
	{

	}

	void TutorialStep03::resumeState()
	{

	}

	void TutorialStep03::pauseState()
	{

	}

	void TutorialStep03::updateState()
	{
	}

	void TutorialStep03::initRender()
	{
		std::unique_ptr<PipelineRendererBase> renderTutorialStep03 = renderPasses::OnlySloid::createRenderer(getWindow()->getRenderContext());
		_members->render = _members->renderContext->createRender("TutorialStep03", std::move(renderTutorialStep03));
		_members->renderPipeline = _members->render->getPipeline<renderPasses::OnlySloid::PipelineRenderer>();
	}

	void TutorialStep03::initTriangle()
	{
		_members->triangle = std::make_unique<Mesh>("triangle");
		std::unique_ptr<BufferContext> bufferContext = _members->renderContext->createBufferContext();
		std::unique_ptr<Material> material = loadMaterial();
		loadTriangleVerticies(material.get(), bufferContext.get());
		loadTriangleIndicies(bufferContext.get());
		bufferContext->finalize();
		_members->triangle->load(std::move(bufferContext), std::move(material));
	}

	void TutorialStep03::initShaders()
	{
		std::string vsPath;
		std::string fsPath;
		std::string vsMain;
		std::string fsMain;
#if TUTORIAL_USE_WINAPI
	
		vsPath = "shaders/hlsl/Tutorial03.hlsl";
		vsMain = "VShader";
		fsPath = "shaders/hlsl/Tutorial03.hlsl";
		fsMain = "PShader";
	
#else
		vsPath = "shaders/glsl/Tutorial03_vs.glsl";
		vsMain = "main";
		fsPath = "shaders/glsl/Tutorial03_fs.glsl";
		fsMain = "main";
#endif
		Context::libraryService()->addShader(ShaderLibraryLabel("tutorial03", FilePath(vsPath), ShaderType::VertexShader, vsMain));
		Context::libraryService()->addShader(ShaderLibraryLabel("tutorial03", FilePath(fsPath), ShaderType::FragmentShader, fsMain));
	}

	void TutorialStep03::loadScene()
	{
		std::unique_ptr<SolidComponentRegister> componentRegister(new SolidComponentRegister());
		_members->scene = Context::application()->getSceneManager()->createScene("TutorialStep03", _members->renderContext, "TutorialStep03", std::move(componentRegister));
		{
			std::unique_ptr<Entity> camera(new Entity("Camera"));
			PerspectiveProjectionSettings settings(glm::radians(70.0f), 0.1f, 100.0f);
			std::unique_ptr<CameraComponent> cameraComponent(new CameraComponent(getWindow(), settings, glm::vec3(0.0f)));
			camera->registerCameraComponent(std::move(cameraComponent));
			camera->registerTransformationComponent(std::make_unique<TransformationComponent>());
			_members->scene->registerEntity(std::move(camera));
		}
		{
			std::unique_ptr<Entity> entity(new Entity("Triangle"));
			_members->triangleEntity = entity.get();
			std::unique_ptr<MeshComponent> meshComponent(new MeshComponent(_members->triangle.get()));
			entity->registerVisualComponent(std::move(meshComponent));
			entity->registerTransformationComponent(std::make_unique<TransformationComponent>());
			_members->scene->registerEntity(std::move(entity));
		}
	}

	std::vector<ShaderResourceDescription> TutorialStep03::createHLSLMaterialParameters() const
	{
		std::vector<ShaderResourceDescription> result;
		result.push_back(ShaderResourceDescription("instanceColor",
						 GPUMemberType::Vec4,
						 ShaderResourceBindingData(0, {ShaderType::VertexShader})));
		result.push_back(ShaderResourceDescription("ProjectionViewWorldMatrix",
						 GPUMemberType::Mat4,
						 ShaderResourceBindingData(1, {ShaderType::VertexShader})));
		return result;
	}

	std::vector<ShaderResourceDescription> TutorialStep03::createGLSLMaterialParameters() const
	{
		std::vector<ShaderResourceDescription> result;
		result.push_back(ShaderResourceDescription("instanceColor",
														   GPUMemberType::Vec4,
														   ShaderResourceBindingData({ ShaderType::VertexShader })));
		result.push_back(ShaderResourceDescription("ProjectionViewWorldMatrix",
						 GPUMemberType::Mat4,
						 ShaderResourceBindingData({ShaderType::VertexShader})));
		return result;
	}

	std::vector<ShaderResourceDescription> TutorialStep03::createMaterialParameters() const
	{
#if TUTORIAL_USE_WINAPI
		return createHLSLMaterialParameters();
#else
		return createGLSLMaterialParameters();
#endif
	}


	std::unique_ptr<Material> TutorialStep03::loadMaterial()
	{

		AttributeFormat layout;
		layout.insertAttribute(GPUMemberType::Vec4, 0, "position");
		layout.insertAttribute(GPUMemberType::Vec4, 1, "color");
#if TUTORIAL_USE_WINAPI
		MaterialDescription description(ShaderVersion::HLSL_5_0);
#else
		MaterialDescription description(ShaderVersion::GLSL_330);
#endif
		description.setFragmentShaderName("tutorial03");
		description.setVertexShaderName("tutorial03");
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

	void TutorialStep03::loadTriangleVerticies(Material* material, BufferContext* bufferContext)
	{
#if TUTORIAL_USE_WINAPI
		// TODO Rasterization propertiy. Vertex binding order must be able to set up clock wise or counter clock wise.
		// https://msdn.microsoft.com/en-us/library/windows/desktop/ff476198(v=vs.85).aspx
		// https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glFrontFace.xml
		std::vector<float> data(
		{
			0.0f, 1.0f, -5.f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			1.0f, -1.0f, -5.f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, -5.f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f
		});
#else
		std::vector<float> data(
		{
			-1.0f, -1.0f, -5.f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			1.0f, -1.0f, -5.f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 1.0f, -5.f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f
		});
#endif
		
		bufferContext->setupVertexBuffer(material->getAttributeFormat(), data);
	}

	void TutorialStep03::loadTriangleIndicies(BufferContext* bufferContext)
	{
		std::vector<int32_t> data = 
		{
			0, 1, 2
		};
		bufferContext->setupIndexBuffer(PrimitiveType::Triangle, data);
	}

	void TutorialStep03::createConnections()
	{
		Keyboard* keyboard = getWindow()->getEventManager()->findEventSource<Keyboard>()[0];
		CONNECT_SIGNAL(keyboard, keyReleased, this, onKeyUp);
	}

	void TutorialStep03::onKeyUp(KeyboardButton button)
	{
		Entity* camera = _members->scene->findCameraEntities()[0];
		switch(button)
		{
			case KeyboardButton::Key_Up:
				_members->triangleEntity->getTransformationComponent()->setWorldPosition(_members->triangleEntity->getTransformationComponent()->getWorldPosition() + vec3(0.0f, 0.20f, 0.0f));
				break;
			case KeyboardButton::Key_Down:
				_members->triangleEntity->getTransformationComponent()->setWorldPosition(_members->triangleEntity->getTransformationComponent()->getWorldPosition() + vec3(0.0f, -0.2f, 0.0f));
				break;
			case KeyboardButton::Key_W:
				camera->getTransformationComponent()->setWorldPosition(camera->getTransformationComponent()->getWorldPosition() + vec3(0.0f, 0.0f, 1.0f));
				break;
			case KeyboardButton::Key_S:
				camera->getTransformationComponent()->setWorldPosition(camera->getTransformationComponent()->getWorldPosition() + vec3(0.0f, 0.0f, -1.0f));
				break;
			case KeyboardButton::Key_A:
				camera->getTransformationComponent()->setWorldPosition(camera->getTransformationComponent()->getWorldPosition() + vec3(-1.0f, 0.0f, 0.0f));
				break;
			case KeyboardButton::Key_D:
				camera->getTransformationComponent()->setWorldPosition(camera->getTransformationComponent()->getWorldPosition() + vec3(1.0f, 0.0f, 0.0f));
				break;
			case KeyboardButton::Key_Space:
				camera->getTransformationComponent()->setWorldPosition(camera->getTransformationComponent()->getWorldPosition() + vec3(0.0f, 1.0f, 0.0f));
				break;
			case KeyboardButton::Key_LCtrl:
				camera->getTransformationComponent()->setWorldPosition(camera->getTransformationComponent()->getWorldPosition() + vec3(0.0f, -1.0f, 0.0f));
				break;
		}		
		vec3 a(0.0f, 0.5f, -1.0f);
		vec3 b(0.45f, -0.5f, 1.0f);
		vec3 c(-0.45f, -0.5f, 1.0f);
		vec3 pA = camera->getCameraComponent()->WorldPointToViewport(a);
		vec3 pB = camera->getCameraComponent()->WorldPointToViewport(b);
		vec3 pC = camera->getCameraComponent()->WorldPointToViewport(c);

		getConsole()->print("a: % % %", pA.x, pA.y, pA.z);
		getConsole()->print("a: % % %", pB.x, pB.y, pB.z);
		getConsole()->print("a: % % %", pC.x, pC.y, pC.z);
	}
}
