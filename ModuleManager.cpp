#include "ModuleManager.hpp"


namespace core{

ModuleManager& ModuleManager::getInstance()
{
	static ModuleManager ins;
	return ins;
}

bool ModuleManager::registerModule(const char* moduleName, IModule * module, int priority)
{
	std::string name = moduleName;

	{
		std::map<std::string, IModule*>::iterator it = m_modules.find(name);
		if(it != m_modules.end())
		{
			return false;
		}
	}
	{
		std::map<std::string, int>::iterator it = m_modulePriority.find(name);
		if(it != m_modulePriority.end())
		{
			return false;
		}

	}

	m_modules[name] = module;
	m_modulePriority[name] = priority;
	return true;

}

bool ModuleManager::activeModule(const char* moduleName)
{
	std::string name = moduleName;
	{
		std::multimap<int, std::string>::iterator it = m_activeModules.begin();
		std::multimap<int, std::string>::iterator end = m_activeModules.end();

		for(; it != end; ++it)
		{
			if(it->second == name)
			{
				break;
			}
		}

		if(it != end)
			return false;
	}

	{
		std::map<std::string, IModule*>::iterator it = m_modules.find(name);
		if(it == m_modules.end())
		{
			return false;
		}
	}

	m_activeModules.insert(std::pair<int,std::string>(m_modulePriority[name], name));
	return true;
}

IModule * ModuleManager::findModule(const char* moduleName)
{
	std::string name = moduleName;
	{
		std::multimap<int, std::string>::iterator it = m_activeModules.begin();
		std::multimap<int, std::string>::iterator end = m_activeModules.end();

		for(; it != end; ++it)
		{
			if(it->second == name)
			{
				break;
			}
		}

		if(it == end)
			return NULL;
	}

	{
		std::map<std::string, IModule*>::iterator it = m_modules.find(name);
		if(it == m_modules.end())
		{
			return NULL;
		}
		return it->second;
	}
}

bool ModuleManager::initModule()
{
	std::multimap<int, std::string>::iterator it = m_activeModules.begin();
	std::multimap<int, std::string>::iterator end = m_activeModules.end();
	for(;it != end; ++it)
	{
		std::map<std::string, IModule*>::iterator iter = m_modules.find(it->second);
		if(iter == m_modules.end() )
		{
			return false;
		}
		if(iter->second->onInit() == false)
		{
			return false;
		}
	}
	return true;
}

bool ModuleManager::saveModule()
{
	std::multimap<int, std::string>::iterator it = m_activeModules.begin();
	std::multimap<int, std::string>::iterator end = m_activeModules.end();
	for(;it != end; ++it)
	{
		std::map<std::string, IModule*>::iterator iter = m_modules.find(it->second);
		if(iter == m_modules.end() )
		{
			return false;
		}
		if(iter->second->onSave() == false)
		{
			return false;
		}
	}

	return true;
}

bool ModuleManager::destoryModule()
{
	std::multimap<int, std::string>::iterator it = m_activeModules.begin();
	std::multimap<int, std::string>::iterator end = m_activeModules.end();
	for(;it != end; ++it)
	{
		std::map<std::string, IModule*>::iterator iter = m_modules.find(it->second);
		if(iter == m_modules.end() )
		{
			return false;
		}
		if(iter->second->onDestroy() == false)
		{
			return false;
		}
	}

	return true;
}

ModuleCreator::ModuleCreator(const char * moduleName, IModule * module, int priority)
{
	ModuleManager::getInstance().registerModule(moduleName, module, priority);
}

}