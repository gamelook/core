#include "Script.hpp"
#include "utils.hpp"
#include "typedef.hpp"

extern "C"{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
};
#include <stdarg.h>
#include <stdio.h>

namespace core{

Script::Script():
	m_lua(NULL)
{

}

Script::~Script()
{
	finit();
}

Script& Script::getInstance()
{
	static Script ins;
	return ins;
}

int Script::getFieldInt(const char * fieldName)
{
	lua_settop(m_lua, 0);
	lua_getglobal(m_lua, fieldName);
	if(!lua_isnumber(m_lua, 1))
	{
		lua_pop(m_lua, 1);
		return 0;
	}

	int value = (int)lua_tonumber(m_lua, 1);
	lua_pop(m_lua, 1);
	return value;
}

float Script::getFieldFloat(const char * fieldName)
{
	lua_settop(m_lua, 0);
	lua_getglobal(m_lua, fieldName);
	if(!lua_isnumber(m_lua, 1))
	{
		lua_pop(m_lua, 1);
		return 0;
	}

	float value = (float)lua_tonumber(m_lua, 1);
	lua_pop(m_lua, 1);
	return value;
}

String Script::getFieldStr(const char *fieldName)
{
	lua_settop(m_lua, 0);
	lua_getglobal(m_lua, fieldName);
	if(!lua_isstring(m_lua, 1))
	{
		lua_pop(m_lua, 1);
		return "";
	}

	String value = lua_tostring(m_lua, 1);
	lua_pop(m_lua, 1);
	return value;
}


bool Script::callFunc(const char * func)
{
	lua_settop(m_lua,0);
	int status = luaL_loadstring(m_lua, func);
	if (status != 0)
		return false;
	if(lua_pcall(m_lua, 0, -1, 0) != 0)
		return false;
	
	return true;
}

bool Script::callFunc(const char * func, const char * sig, ...)
{
	lua_settop(m_lua,0);
	va_list vl;

	int narg, nres;   /* number of arguments and results */



	va_start(vl, sig);

	lua_getglobal(m_lua, func);  /* get function */



	/* push arguments */

	narg = 0;

	while (*sig) {    /* push arguments */

		switch (*sig++) {



		case 'd':  /* double argument */

			{
				double a = va_arg(vl, double);
				lua_pushnumber(m_lua, a);

			}


			break;



		case 'i':  /* int argument */

			{
				int a = va_arg(vl, int);
				lua_pushnumber(m_lua, a);

			}

			break;



		case 's':  /* string argument */

			lua_pushstring(m_lua, va_arg(vl, char *));

			break;



		case '>':

			goto endwhile;



		default:
			;
//			error(L, "invalid option (%c)", *(sig - 1));

		}

		narg++;

		luaL_checkstack(m_lua, 1, "too many arguments");

	} endwhile:



	/* do the call */

	nres = strlen(sig);  /* number of expected results */

	if (lua_pcall(m_lua, narg, nres, 0) != 0)  /* do the call */
		printf("error %s", lua_tostring(m_lua, -1));
//		error(L, "error running function `%s': %s",


//		func, lua_tostring(m_lua, -1);



	/* retrieve results */

	nres = -nres;     /* stack index of first result */

	while (*sig) {    /* get results */

		switch (*sig++) {



		case 'd':  /* double result */

			if (!lua_isnumber(m_lua, nres))

;//				error(L, "wrong result type");

			{
				double  ret = lua_tonumber(m_lua, nres);
				*va_arg(vl, double *) = ret;

			}

			break;



		case 'i':  /* int result */
			{

			if (!lua_isnumber(m_lua, nres))
				;

			int ret = (int)lua_tonumber(m_lua, nres);

			*va_arg(vl, int *) = ret;
			}

			break;



		case 's':  /* string result */

			if (!lua_isstring(m_lua, nres))

		;//		error(L, "wrong result type");

			*va_arg(vl, String *) = lua_tostring(m_lua, nres);

			break;



		default:

			;//error(L, "invalid option (%c)", *(sig - 1));

		}

		nres++;

	}

	va_end(vl);
	return false;

}

//int Script::callScript(const char * script)
//{
//
//	core::String func = script;
//	int m = func.find('.');
//	if(m != -1)
//	{
//		core::String module = func.substr(0,m);
//		func = func.substr(m+1, func.size());
//	}
//
//	int idx = func.find('(');
//	if(idx == -1)
//		return -1;
//
//	core::String name = func.substr(0, idx);
//	lua_getglobal(m_lua, name.c_str());
//
//	int idx1 = func.find(')');
//	if(idx1 == -1)
//		return -1;
//
//	Vector<String> args;
//	split(func.substr(idx+1, idx1-idx-1), ',', args);
//
//	for(int i = 0; i < args.size(); ++i)
//	{
//		double v = atof(args[i].c_str());
//		lua_pushnumber(m_lua, v);
//	}
//
//	if(lua_pcall(m_lua, args.size(), 1, 0) != 0)
//		return -1;
//
//	int ret = (int)lua_tonumber(m_lua, -1);
//
//	return ret;
//}

int Script::callScript(const char* fmt, ...)
{
	static char  buffer[1024];
	va_list argptr;
	va_start(argptr, fmt);
	vsnprintf(buffer,sizeof(buffer),fmt,argptr);
#ifdef WIN32
	buffer[sizeof(buffer)-1] = '\0';
#endif

	core::String func = buffer;
	int m = func.find('.');
	if(m != -1)
	{
		core::String module = func.substr(0,m);
		func = func.substr(m+1, func.size());
	}

	int idx = func.find('(');
	if(idx == -1)
		return -1;

	core::String name = func.substr(0, idx);
	lua_getglobal(m_lua, name.c_str());

	int idx1 = func.find(')');
	if(idx1 == -1)
		return -1;

	Vector<String> args;
	split(func.substr(idx+1, idx1-idx-1), ',', args);

	for(int i = 0; i < args.size(); ++i)
	{
		double v = atof(args[i].c_str());
		lua_pushnumber(m_lua, v);
	}

	if(lua_pcall(m_lua, args.size(), 1, 0) != 0)
		return -1;

	int ret = (int)lua_tonumber(m_lua, -1);

	return ret;
}

int Script::callScript(const char * script, const char* sig, ...)
{

	va_list vl;
	va_start(vl, sig);

	lua_getglobal(m_lua, script);  /* get function */



	/* push arguments */
	int narg = 0;
	while (*sig) 
	{
		switch (*sig++) 
		{
		case 'd':  /* double argument */
			{
				double a = va_arg(vl, double);
				lua_pushnumber(m_lua, a);

			}
			break;
		case 'i':  /* int argument */
			{
				int a = va_arg(vl, int);
				lua_pushnumber(m_lua, a);
			}
			break;
		case 's':  /* string argument */
			lua_pushstring(m_lua, va_arg(vl, char *));
			break;
		default:
			;
		}
		narg++;
		luaL_checkstack(m_lua, 1, "too many arguments");
	} 


	if (lua_pcall(m_lua, narg, 1, 0) != 0)  /* do the call */
		printf("error %s", lua_tostring(m_lua, -1));

	int ret = (int)lua_tonumber(m_lua, -1);

	va_end(vl);

	return ret;
}

bool Script::load(const String& filename)
{
	return load(filename.c_str());
}

bool Script::load(const char * filename)
{
	if (luaL_loadfile(m_lua, filename) || lua_pcall(m_lua, 0, -1, 0))
	{
		return false;
	}
	return true;
}

lua_State * Script::getLuaState()
{
	return m_lua;
}

void Script::init()
{
	//m_lua = lua_open();

	//luaopen_base(m_lua);
	m_lua = luaL_newstate();
	luaL_openlibs(m_lua);

}

void Script::finit()
{
	if(m_lua != NULL)
	{
		lua_close(m_lua);
		m_lua = NULL;		
	}
}

}

