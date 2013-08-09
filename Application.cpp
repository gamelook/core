#include "IOService.hpp"
#include "Script.hpp"
#include "Application.hpp"
#include "MemPool.hpp"


namespace core {

//bool mem_init();
//void mem_finit();

Application::Application()
{

}

Application::~Application()
{

}

void Application::run(int argc, char* argv[])
{
	mem_init();
	Script::getInstance().init();
	IOService::init();
	IOService::run(this, argc, argv);
	IOService::finit();
	Script::getInstance().finit();
	mem_finit();
}


}

