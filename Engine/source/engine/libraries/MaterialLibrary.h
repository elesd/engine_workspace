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

		void addMateria(const std::string& materialName, const MaterialDescription& description);
		MaterialInstance* findMaterial(const std::string& name);

		bool isInitialized() const;
	private:
		struct MaterialLibraryPrivate* _members = nullptr;
	};
}