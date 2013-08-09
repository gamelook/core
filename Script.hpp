#ifndef CORE_CORE_SCRIPT_H__
#define  CORE_CORE_SCRIPT_H__

#include <string>
#include "typedef.hpp"

struct lua_State;

namespace core{

class Script
{
private:
	Script();
public:
	~Script();

	static Script& getInstance();

	bool load(const String& filename);

	bool load(const char * fileName);

	int getFieldInt(const char * fieldName);
	float getFieldFloat(const char * fieldName);
	String getFieldStr(const char *fieldName);

	bool callFunc(const char * func);
	bool callFunc(const char * func, const char * fmt, ...);
//	int callScript(const char * script);
	int callScript(const char* fmt, ...);
	int callScript(const char * script, const char* fmt, ...);

	lua_State * getLuaState();

	void init();
	void finit();



private:

	lua_State * m_lua;

};

}

#endif //CORE_CORE_SCRIPT_H__

