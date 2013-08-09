#include "DispatchTable.hpp"
#include <memory.h>
#include <assert.h>

namespace core {

DispatchTable::DispatchTable()
{

}

DispatchTable::~DispatchTable()
{

}

void DispatchTable::init()
{
	for(int i = 0; i < MAX_LEN; ++i)
	{
		m_handler[i] = NULL;
	}
}

void DispatchTable::finit()
{
	for(int i = 0; i < MAX_LEN; ++i)
	{
		if(m_handler[i] != NULL)
		{
			delete m_handler[i];
			m_handler[i] = NULL;
		}
	}
}

DispatchTable & DispatchTable::getInstance()
{
	static DispatchTable instance;
	return instance;
}

bool DispatchTable::dispatch(int connectionID, char * buf, int size)
{
	MessageID mid = *((MessageID*)buf);
	if(m_handler[mid] != NULL)
	{
		m_handler[mid]->execute(connectionID, buf, size);
		return true;
	}
	else
	{
		return false;
	}
}

bool DispatchTable::dispatch(int connectionID, int userID, char * buf, int size)
{
	MessageID mid = *((MessageID*)buf);
	if(m_handler[mid] != NULL)
	{
		m_handler[mid]->execute(connectionID, userID, buf, size);
		return true;
	}
	else
	{
		return false;
	}
}

bool DispatchTable::registerMessageHandler(MessageID mid, MessageHandler* handler)
{
	if(m_handler[mid] == NULL)
	{
		m_handler[mid] = handler;
		return true;
	}
	else
	{
		assert(0);
		return false;
	}
}

void registerHandler(MessageID mid, void (*func)(int, char *, int))
{
	DispatchTable::getInstance().registerMessageHandler(mid,\
		new MessageHandlerT<void (int, char *, int)>(func));
}

}

