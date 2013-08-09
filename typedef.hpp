#ifndef CORE_CORE_TYPEDEF_H__
#define CORE_CORE_TYPEDEF_H__

#include <map>
#include <set>
#include <vector>
#include <list>
#include <string>
#include "MemPool.hpp"


namespace core {

typedef signed char               int8_t;
typedef unsigned char           uint8_t;
typedef short                       int16_t;
typedef unsigned short          uint16_t;
typedef int                           int32_t;
typedef unsigned int              uint32_t;
typedef long long                  int64_t;
typedef unsigned long long    uint64_t;
typedef unsigned short          MessageID;
typedef unsigned int             UserID;
typedef unsigned int             MsgLength;
typedef int                          ConnectionID;
typedef unsigned short         StrLength;
typedef long long                 ID;

#ifndef USE_MEM_POOL



typedef std::string   String;

template <typename _Ty>
class Vector:
	public std::vector<_Ty>
{

};


template <typename _Ty>
class List:
	public std::list<_Ty>
{

};


template <typename _Kty, typename _Ty>
class Map:
	public std::map<_Kty, _Ty>
{

};

template <typename _Kty>
class Set:
	public std::set<_Kty>
{

};

#else

class String:
	public Pool,
	public std::basic_string<char, std::char_traits<char>, Allocator<char> >
{
public:
	String()
	{

	}

	String(const char* v):
	  std::basic_string<char, std::char_traits<char>, Allocator<char> >(v)
	{
	}

	String(const std::basic_string<char, std::char_traits<char>, Allocator<char> > & v):
		std::basic_string<char, std::char_traits<char>, Allocator<char> >(v)
	{

	}



	String& operator=(const char * v)
	{
		std::basic_string<char, std::char_traits<char>, Allocator<char> >::operator=(v);
		return *this;
	}

	//String& operator=(const String& v)
	//{
	//	std::basic_string<char, std::char_traits<char>, Allocator<char> >::operator=(v.c_str());
	//	return *this;
	//}



};

template <typename _Ty>
class Vector:
	public Pool,
	public std::vector<_Ty, Allocator<_Ty> >
{

};


template <typename _Ty>
class List:
	public Pool,
	public std::list<_Ty, Allocator<_Ty> >
{

};


template <typename _Kty, typename _Ty>
class Map:
	public Pool,
	public std::map<_Kty, _Ty, std::less<_Kty>, Allocator< std::pair<const _Kty, _Ty> > >
{

};

template <typename _Kty>
class Set:
	public Pool,
	public std::set<_Kty, std::less<_Kty>, Allocator<_Kty> >
{

};

#endif



/*
	type: 0连接，1接收数据，2连接断开，3连接失败, 4数据包太大
*/
typedef void (*network_cb)(int type, int connectionID, char * buf, int size);

class NetEvent
{
public:
	const static int Connected      = 0; //连接
	const static int DataRecv       = 1; //接收数据
	const static int Disconnected  = 2; //连接断开
	const static int ConnectFailed = 3; //连接失败
	const static int PkgError         = 4; //数据包太大
};


class ProtoType
{
public:
	const static int PT_TCP = 0;
	const static int PT_HTTP = 1;
};


}






#endif //CORE_CORE_TYPEDEF_H__

