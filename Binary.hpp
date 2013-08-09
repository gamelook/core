#ifndef CORE_CORE_BINARY_H__
#define  CORE_CORE_BINARY_H__

#include "OutRange.hpp"

namespace core{

struct Binary
{
	String buf;
};

template <typename AR>
AR& operator >> (AR& ar, Binary& data)
{
	int32_t size;
	ar >> size;
	if(size > ar.getRemainSize())
		throw OutRange();
	data.buf.assign(ar.getRemain(), size);
	ar.skip(size);
	return ar;
}

template <typename AR>
AR& operator << (AR& ar, const Binary& data)
{
	ar << (int32_t)data.buf.size();
	ar.write((char*)data.buf.c_str(), data.buf.size());
	return ar;
}

}
#endif //CORE_CORE_BINARY_H__
