#include "OStream.hpp"
#include "string.h"

namespace core {
OStream::OStream(size_t size):
	m_size(size),
	m_cur(0)
{
	m_buf = (char*)core_malloc(m_size);
	
}

OStream::~OStream()
{
	core_free(m_buf, m_size);
}

void OStream::write(char * buf, size_t size)
{
	enoughFreeSpace(size);

	memcpy(&m_buf[m_cur], buf, size);
	m_cur += (int)size;

}

void OStream::enoughFreeSpace(size_t size)
{
	while(freeSpace() < size)
	{
		resize();
	}
}

size_t OStream::freeSpace()
{
	return m_size - m_cur;
}

void OStream::resize()
{
	
	char * buf = (char*)core_malloc(m_size*2);
	memcpy(buf, m_buf, m_size);
	core_free(m_buf, m_size);
	m_buf = buf;
	m_size *= 2;
	

}

char * OStream::getBuf()
{
	return m_buf;
}
int OStream::getSize()
{
	return m_cur;
}

void OStream::skip(int offset)
{
	m_cur += offset;
}

OStream& OStream::operator << (char v)
{
	return write(v);
}

OStream& OStream::operator << (unsigned char v)
{
	return write(v);

}

OStream& OStream::operator << (signed char v)
{
	return write(v);

}

OStream& OStream::operator << (unsigned short v)
{
	return write(v);

}

OStream& OStream::operator << (short v)
{
	return write(v);

}

OStream& OStream::operator << (unsigned int v)
{
	return write(v);

}

OStream& OStream::operator << (int v)
{
	return write(v);

}

OStream& OStream::operator << (unsigned long v)
{
	return write(v);

}

OStream& OStream::operator << (long v)
{
	return write(v);

}

OStream& OStream::operator << (unsigned long long v)
{
	return write(v);

}

OStream& OStream::operator << (long long v)
{
	return write(v);

}

OStream& OStream::operator << (float v)
{
	return write(v);
}

OStream& OStream::operator << (double v)
{
	return write(v);
}

OStream& OStream::operator << (const String& v)
{
	StrLength size = (StrLength)v.size();
	write(size);
	write((char *)v.c_str(), size);
	return *this;

}
}

