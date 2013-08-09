#include "IStream.hpp"
#include "OutRange.hpp"

namespace core {

IStream::IStream(char* buf, size_t size):
	m_buf(buf),
	m_read(0),
	m_size(size)
{

}

IStream::~IStream()
{

}

char * IStream::getRemain()
{
	return &m_buf[m_read];
}

int IStream::getRemainSize()
{
	return m_size - m_read;
}

void IStream::skip(int offset)
{
	m_read += offset;
}

IStream& IStream::operator >> (char& v)
{
	return read(v);
}

IStream& IStream::operator >> (unsigned char& v)
{
	return read(v);

}

IStream& IStream::operator >> (signed char& v)
{
	return read(v);

}

IStream& IStream::operator >> (unsigned short& v)
{
	return read(v);

}

IStream& IStream::operator >> (short& v)
{
	return read(v);

}

IStream& IStream::operator >> (unsigned int& v)
{
	return read(v);

}

IStream& IStream::operator >> (int& v)
{
	return read(v);

}

IStream& IStream::operator >> (unsigned long& v)
{
	return read(v);
}

IStream& IStream::operator >> (long& v)
{
	return read(v);
}

IStream& IStream::operator >> (unsigned long long& v)
{
	return read(v);

}

IStream& IStream::operator >> (long long& v)
{
	return read(v);

}
IStream& IStream::operator >> (float& v)
{
	return read(v);
}
IStream& IStream::operator >> (double& v)
{
	return read(v);
}

IStream& IStream::operator >> (String& v)
{
	StrLength size;
	read(size);
	enoughData(size);
	v.assign(&m_buf[m_read],size);
	m_read += size;
	return *this;

}

void IStream::enoughData(size_t size)
{
	if(m_size-m_read < size)
	{
		throw OutRange();
	}
}

}

