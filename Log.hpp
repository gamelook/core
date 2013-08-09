#ifndef NODE_KERNEL_LOG_H__
#define NODE_KERNEL_LOG_H__

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/stringhelper.h>
#include <log4cplus/helpers/timehelper.h>
#include <log4cplus/spi/loggingevent.h>
#include <stdio.h>
#include <stdarg.h>
#include "typedef.hpp"

using namespace log4cplus;
using namespace log4cplus::helpers;

void logprint(core::String& s, const char *fmt, ...);

#define LOG_DEBUG(LOGGER, FORMAT, ...)  do{\
	core::String s;\
	logprint(s, FORMAT, ##__VA_ARGS__);\
	LOG4CPLUS_DEBUG(LOGGER, s.c_str() );\
}while(0)

#define LOG_WARN(LOGGER, FORMAT, ...)  do{\
	core::String s;\
	logprint(s, FORMAT, ##__VA_ARGS__);\
	LOG4CPLUS_WARN(LOGGER, s.c_str() );\
}while(0)

#define LOG_ERROR(LOGGER, FORMAT, ...)  do{\
	core::String s;\
	logprint(s, FORMAT, ##__VA_ARGS__);\
	LOG4CPLUS_ERROR(LOGGER, s.c_str() );\
}while(0)

#define LOG_FATAL(LOGGER, FORMAT, ...)  do{\
	core::String s;\
	logprint(s, FORMAT, ##__VA_ARGS__);\
	LOG4CPLUS_FATAL(LOGGER, s.c_str() );\
}while(0)

#endif //NODE_KERNEL_LOG_H__

