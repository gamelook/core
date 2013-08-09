#ifndef CORE_LOGMANAGER_H__
#define CORE_LOGMANAGER_H__

#include "typedef.hpp"
#include <stdio.h>

namespace core{

	class LogManager
	{
	private:
		LogManager(){}

	public:
		static LogManager& getInstance()
		{
			static LogManager ins;
			return ins;
		}

		bool open(char * filename);
		void print(const char *fmt, ...);
		void close();

	private:
		core::String m_filename;
		int m_maxLine;
		int m_curLine;
		int m_curfile;
		FILE* m_fp;

	};
}
#endif //CORE_LOGMANAGER_H__