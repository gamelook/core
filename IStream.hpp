#ifndef CORE_CORE_ISTREAM_H__
#define CORE_CORE_ISTREAM_H__

#include "typedef.hpp"

namespace core
{

class  IStream
{
public:
	IStream(char* buf, size_t size);
	~IStream();

	char * getRemain();
	int getRemainSize();
	void skip(int offset);

	IStream& operator >> (char& v);
	IStream& operator >> (unsigned char& v);
	IStream& operator >> (signed char& v);
	IStream& operator >> (unsigned short& v);
	IStream& operator >> (short& v);
	IStream& operator >> (unsigned int& v);
	IStream& operator >> (int& v);
	IStream& operator >> (unsigned long& v);
	IStream& operator >> (long& v);
	IStream& operator >> (unsigned long long& v);
	IStream& operator >> (long long& v);
	IStream& operator >> (float& v);
	IStream& operator >> (double& v);
	IStream& operator >> (String& v);

	template <typename T>
	IStream& operator >> (Vector<T>& v);

private:
	void enoughData(size_t size);
	
	template <typename T>
	IStream& read(T & v);

private:
	char*  m_buf;
	int     m_read;
	size_t m_size;
	int    m_endian;
};

template <typename T>
inline IStream& IStream::read(T & v)
{
	size_t size = sizeof(T);
	enoughData(size);

	v = *((T*)(&m_buf[m_read]));

	m_read += size;
	return *this;
}


template <typename T>
inline IStream& IStream::operator >> (Vector<T>& v)
{
	uint16_t size;
	read(size);
	for(uint16_t i = 0; i < size; ++i)
	{
		T t;
		*this >> t;
		v.push_back(t);
	}
	return *this;
}

}
#endif //CORE_CORE_ISTREAM_H__


