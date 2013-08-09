#include "Log.hpp"

void logprint(core::String& s, const char *fmt, ...)
{
	static char  buffer[1024*1024];
	va_list argptr;
	va_start(argptr, fmt);
	vsnprintf(buffer,sizeof(buffer),fmt,argptr);
#ifdef WIN32
	buffer[sizeof(buffer)-1] = '\0';
#endif
	s = buffer;
}