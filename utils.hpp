#ifndef CORE_CORE_UTILS_H__
#define CORE_CORE_UTILS_H__

#include "typedef.hpp"

namespace core{

	void getStackInfo(String& stackInfo);
	unsigned int hashToInt(const String& s, unsigned int maxInt);
	char * itos(int v);

	void split(core::String src, char c, core::Vector<core::String>& dst);

}

#endif //CORE_CORE_UTILS_H__

