#ifndef CORE_CORE_DISPATCHTABLE_H__
#define CORE_CORE_DISPATCHTABLE_H__

#include "typedef.hpp"
#include "MessageHandler.hpp"



#define REGISTER_MESSAGE(ID,HANDLER)\
	core::registerHandler(ID,HANDLER)

namespace core{

class  DispatchTable
{
	enum {MAX_LEN=0x10000};
public:
	void init();
	void finit();

	static DispatchTable & getInstance();

	bool dispatch(int connectionID, char * buf, int size);
	bool dispatch(int connectionID, int userID, char * buf, int size);
	bool registerMessageHandler(MessageID mid, MessageHandler* handler);

private:
	DispatchTable();
	~DispatchTable();

private:
	MessageHandler * m_handler[MAX_LEN];

};

void registerHandler(MessageID mid, void (*func)(int, char*, int));

template <typename T>
inline void registerHandler(MessageID mid, void (*func)(int, T&))
{
	DispatchTable::getInstance().registerMessageHandler(mid,\
		new MessageHandlerT<void (int,T&)>(func));
}

template <typename T>
inline void registerHandler(MessageID mid, void (*func)(int, int, T&))
{
	DispatchTable::getInstance().registerMessageHandler(mid,\
		new MessageHandlerT<void (int,int,T&)>(func));
}

template <typename T>
inline void registerHandler(MessageID mid, void (*func)(int, T&, IStream&))
{
	DispatchTable::getInstance().registerMessageHandler(mid,\
		new MessageHandlerT<void (int,T&,IStream&)>(func));
}

template <typename T>
inline void registerHandler(MessageID mid, void (*func)(int, int, T&, IStream&))
{
	DispatchTable::getInstance().registerMessageHandler(mid,\
		new MessageHandlerT<void (int,int, T&,IStream&)>(func));
}
}
#endif //CORE_CORE_DISPATCHTABLE_H__
