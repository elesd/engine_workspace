#pragma once

#include <engine/environmentBuilder/BaseBuilder.h>

namespace engine
{
	struct FileSystemSettings;
	class EventBuilder;
	enum class ContextModuleType;
	class FileSystemBuilder : public BaseBuilder
	{
		friend class ApplicationBuilder;
	private:
		FileSystemBuilder(Application *app, const ContextModuleType windowModule);
	public:
		/**PIMPL*/
		FileSystemBuilder(FileSystemBuilder &&o);

		~FileSystemBuilder() override;
		EventBuilder build(const FileSystemSettings &settings);
	private:
		struct FileSystemBuilderPrivate* _members = nullptr;
	};
}