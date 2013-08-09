#ifndef CORE_CORE_OSTREAM_H__
#define CORE_CORE_OSTREAM_H__

#include "typedef.hpp"

namespace core
{

class  OStream
{
public:
	OStream(size_t size = 64);
	~OStream();

	void write(char * buf, size_t size);
	char * getBuf();
	int getSize();
	void skip(int offset);

	OStream& operator << (char v);
	OStream& operator << (unsigned char v);
	OStream& operator << (signed char v);
	OStream& operator << (unsigned short v);
	OStream& operator << (short v);
	OStream& operator << (unsigned int v);
	OStream& operator << (int v);
	OStream& operator << (unsigned long v);
	OStream& operator << (long v);
	OStream& operator << (unsigned long long v);
	OStream& operator << (long long v);
	OStream& operator << (float v);
	OStream& operator << (double v);
	OStream& operator << (const String& v);

	template <typename T>
	OStream& operator << (const Vector<T>& v);

private:
	template <typename T>
	OStream& write(T v);

	void enoughFreeSpace(size_t size);
	size_t freeSpace();
	void resize();

private:
	char*    m_buf;
	int        m_cur;
	int        m_size;


};

template <typename T>
OStream& OStream::write(T v)
{
	size_t size = sizeof(T);
	enoughFreeSpace(size);
	
	*((T*)(&m_buf[m_cur])) = v;
	
	m_cur += (int)size;
	return *this;
}


template <typename T>
inline OStream& OStream::operator << (const Vector<T>& v)
{
	uint16_t size = v.size();
//	assert(v.size() < 0xffff);
	write(size);
	for(uint16_t i = 0; i < size; ++i)
	{
		*this << v[i];
	}
	return *this;
}

}
#endif //CORE_CORE_OSTREAM_H__
