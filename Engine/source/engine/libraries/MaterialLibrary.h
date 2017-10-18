#pragma once

namespace engine
{
	class RenderContext;
	class MaterialDescription;
	class MaterialInstance;

	class MaterialLibrary final
	{
	public:
		MaterialLibrary();
		~MaterialLibrary();

		void init(const std::string& windowName, RenderContext*);

		void addMaterial(const std::string& materialName, const MaterialDescription& description);
		bool hasMaterial(const std::string& materialName);
		std::unique_ptr<MaterialInstance> getMaterial(const std::string& name);

		bool isInitialized() const;
	private:
		struct MaterialLibraryPrivate* _members = nullptr;
	};
}