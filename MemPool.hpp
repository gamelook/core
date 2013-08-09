#ifndef CORE_CORE_MEMPOOL_H__
#define CORE_CORE_MEMPOOL_H__

#include <iostream>
#include <vector>

namespace core{

#ifndef USE_MEM_POOL

#define core_malloc(size)     malloc(size)
#define core_free(mem,size)  free(mem)

class Pool
{
public:

};

#else

bool mem_init();
void mem_finit();
void * core_malloc(size_t size);
void core_free(void * p, size_t size);


class Pool
{
public:
	static void * operator new(size_t size)
	{
		return core_malloc(size);
	}

	static void operator delete(void * mem,size_t size)
	{
		core_free(mem,size);
	}

	static void* operator new(size_t size,const std::nothrow_t& )throw()
	{
		try
		{
			return core_malloc(size);
		}																	
		catch (std::exception &)
		{
			return NULL;
		}
	} 

	static void * operator new[](size_t size)	
	{
		return core_malloc(size);
	}
	
	static void operator delete[](void * mem,size_t size)
	{
		core_free(mem,size);
	}

};

#endif 

#include "Allocator.hpp"

}

#endif //CORE_CORE_MEMPOOL_H__

