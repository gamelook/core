#ifndef CORE_CORE_MODULEMANAGER_H__
#define CORE_CORE_MODULEMANAGER_H__

#include <string>
#include <map>
#include <set>

namespace core{

class IModule
{
public:
	IModule(){}
	virtual ~IModule(){}
	virtual bool onInit() = 0;
	virtual bool onSave(){return true;}
	virtual bool onDestroy() = 0;
};



class ModuleManager
{
public:
	static ModuleManager& getInstance();
	bool registerModule(const char* moduleName, IModule * module,int priority);
	bool activeModule(const char* moduleName);
	IModule * findModule(const char* moduleName);
	bool initModule();
	bool saveModule();
	bool destoryModule();

private:
	std::map<std::string, IModule *> m_modules;
	std::map<std::string, int> m_modulePriority;
	std::multimap<int, std::string> m_activeModules;
};


class ModuleCreator
{
public:
	//����ԽС������Խ�ߣ���ʼ��ģ���ʱ�����ȼ��Ӹߵ���
	ModuleCreator(const char * moduleName, IModule * module, int priority = 1);
};

}

#endif //CORE_CORE_MODULEMANAGER_H__

