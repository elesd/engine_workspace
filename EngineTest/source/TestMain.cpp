#include "stdafx.h"

#include "SignalSlotRegression.h"
#include "FunctionsRegression.h"
#include "StateStackRegression.h"
#include "FileSystemRegression.h"
#include "engine/test/TestManager.h"
#include "EngineTestConfig.h"
#include "engine/EngineConfig.h"

int main(char **args, size_t nArgs)
{
	version::Version::createInstance();
	engine::version::Version::createInstance();
	std::cout << "Engine version: " << engine::version::Version::getInstance()->getString() << std::endl;
	std::cout << "Test version: " << version::Version::getInstance()->getString() << std::endl;
	if((*engine::version::Version::getInstance()) <= (*version::Version::getInstance()))
	{
		engine::test::TestManager manager;
		manager.addRegression(std::move(tests::SignalSlotRegression()));
		manager.addRegression(tests::FunctionsRegression());
		manager.addRegression(tests::StateStackRegression());
		manager.addRegression(tests::FileSystemRegression());
		manager.run();
	}
	else
	{
		std::cout << "Test is outdated!" << std::endl;
	}
	int32_t i;
	std::cin >> i;
	return 0;
}
