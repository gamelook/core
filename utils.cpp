#include "utils.hpp"

#ifdef WIN32
#include <windows.h>
#include <stdio.h>   
#include <dbghelp.h>
#include <string>
#pragma comment( lib, "dbghelp.lib" )
#endif

#include <stdlib.h>

namespace core{

#ifdef WIN32
	//!最大调用栈深度
	const int MAX_STACKS=128;
	struct OFFSET_ARRAY
	{
		OFFSET_ARRAY()
		{
			memset(stacks,0,sizeof(stacks));
		}
		bool operator < (const OFFSET_ARRAY & o) const
		{
			return memcmp(stacks,o.stacks,sizeof(stacks))<0;
		}

		unsigned long long stacks[MAX_STACKS+1];
	};

	static OFFSET_ARRAY getStackInfo()   
	{
		OFFSET_ARRAY stacks;
		const int kMaxCallers = 128;  

		void* callers[kMaxCallers]; 
		int count = CaptureStackBackTrace(3, kMaxCallers, callers, NULL); 
		for(int i = 0; i < count; i++) 
		{ 
			stacks.stacks[i] = (DWORD64)callers[i];
		}
		return stacks;
	}

	static void getStackInfo(String& stack, const OFFSET_ARRAY &stacks)
	{		
		HANDLE        hProcess;
		hProcess = GetCurrentProcess();

		for(int i = 0;stacks.stacks[i]!=0;++i)
		{
			ULONG64 buffer[(sizeof(SYMBOL_INFO)+MAX_SYM_NAME*sizeof(TCHAR)+sizeof(ULONG64)-1)/sizeof(ULONG64)];
			PSYMBOL_INFO pSymbol = (PSYMBOL_INFO)buffer;
			pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
			pSymbol->MaxNameLen = MAX_SYM_NAME;

			DWORD64 dwDisplacement = 0;
			if (SymFromAddr(hProcess,stacks.stacks[i], &dwDisplacement, pSymbol))
			{
				stack += pSymbol->Name;
				stack += "\n";;   
			}
			else
			{
				continue;
			}

			IMAGEHLP_LINE64 lineInfo = { sizeof(IMAGEHLP_LINE64) };   
			DWORD dwLineDisplacement;   

			if( SymGetLineFromAddr64( hProcess, stacks.stacks[i], &dwLineDisplacement, &lineInfo ) )   
			{
				char buf[1024];
				sprintf(buf, "    file:%s\n    line %u\n",lineInfo.FileName,lineInfo.LineNumber);
				stack += buf;
			} 

			if(strcmp(pSymbol->Name,"main")==0)
			{
				break;
			}
			if(strcmp(pSymbol->Name,"wmain")==0)
			{
				break;
			}
			if(strcmp(pSymbol->Name,"BaseThreadInitThunk")==0)
			{
				break;
			}
		}
	}


	void getStackInfo(String& stackInfo)
	{
		OFFSET_ARRAY stacks = getStackInfo();
		getStackInfo(stackInfo, stacks);

	}

#else

#endif


	unsigned int hashToInt(const String& s, unsigned int maxInt)
	{
		unsigned int sum = 0;
		char * buf = (char*)s.c_str();
		for(int i = 0; i < s.size(); ++i)
		{
			int a= (int)buf[i];
			sum += a;
		}

		sum %= maxInt;
		return sum;
	}

	char * itos(int v)
	{
		static char level[20];
		sprintf(level,"%d", v);
		return level;
	}

	void split(core::String src, char c, core::Vector<core::String>& dst)
	{
		int index = src.find_first_not_of(' ');
		if(index == -1)
			return;
		do{

			int idx = src.find(c);
			if(idx != -1)
			{
				core::String sub = src.substr(0, idx);
				src = src.substr(idx+1, src.size());
				dst.push_back(sub);
			}
			else
			{
				dst.push_back(src);
				break;
			}

		}while(1);

	}
}

