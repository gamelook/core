#include "MemPool.hpp"
#include <boost/pool/pool.hpp>

namespace core{

const static int BLOCKMAX = 256;

static boost::pool<>*  g_blocks[BLOCKMAX+1];

bool mem_init()
{
	// {2,4,8,16,32,64,128,256,}
	memset(g_blocks, 0, sizeof(boost::pool<>*)*(BLOCKMAX+1));
	for(int i = 2; i <= BLOCKMAX; i *= 2)
	{
		g_blocks[i] = new boost::pool<>(i);
	}

	for(int k = BLOCKMAX-1; k >= 0; --k)
	{
		if(g_blocks[k] == NULL)
			g_blocks[k] = g_blocks[k+1];
	}

	return true;
}

void mem_finit()
{
	for(int i = 2; i <= BLOCKMAX; i *= 2)
	{
//		delete g_blocks[i];
	}
}

void * core_malloc(size_t size)
{
	if(size <= BLOCKMAX)
	{
		return g_blocks[size]->malloc();
	}
	else
	{
		return ::malloc(size);
	}
}

void core_free(void * p, size_t size)
{
	if(size <= BLOCKMAX)
	{
		g_blocks[size]->free(p);
	}
	else
	{
		::free(p);
	}
}

}

