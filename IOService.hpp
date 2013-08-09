#ifndef CORE_CORE_IOSERVICE_H__
#define CORE_CORE_IOSERVICE_H__

#include "typedef.hpp"
#include "TimerHandler.hpp"
#include <string>
#include "OStream.hpp"


namespace core{

class Application;

class IOService
{
public:
	static bool init();
	static void run(Application * app = NULL,int argc = 0, char* argv[] = NULL);
	static void stop();
	static void finit();

	static int connect(const String& ip, unsigned port, network_cb cb, int sendBufMax = 1024, int recvBufMax = 1024, int proto = ProtoType::PT_TCP);
	static int listen(const String& ip, unsigned port, network_cb cb, int sendBufMax = 1024, int recvBufMax = 1024, int proto = ProtoType::PT_TCP);

	static int connect(const char * ip, unsigned port, network_cb cb, int sendBufMax = 1024, int recvBufMax = 1024, int proto = ProtoType::PT_TCP);
	static int listen(const char * ip, unsigned port, network_cb cb, int sendBufMax = 1024, int recvBufMax = 1024, int proto = ProtoType::PT_TCP);

	static int send(int connectionID, char * buf, int size);

	static void getRemoteAddr(int connectionID, String& ip, unsigned short& port);
	static void getLocalAddr(int connectionID, String& ip, unsigned short& port);
	static void getListenAddr(int listenerID, String& ip, unsigned short& port);

	static void freeConnection(int connectionID);
	static void freeListener(int listenerID);

	static int addTimer(TimerHandler* handler, int interval /*ms*/, int repeat = 1, int offset = 0 /*s*/);
	static void removeTimer(int tid);

	static int gettimeofday();

	template<typename T>
	static int sendMsg(int connectionID, const T& data);


};

template<typename T>
int IOService::sendMsg(int connectionID, const T& data)
{
	OStream os;
	os << int(0);
	os << data;
	*((int*)os.getBuf()) = os.getSize()-4;
	return IOService::send(connectionID, os.getBuf(), os.getSize());
}

}

#endif //CORE_CORE_IOSERVICE_H__

