#ifndef CORE_CORE_LISTENER_H__
#define CORE_CORE_LISTENER_H__


#include "typedef.hpp"

extern "C" {
#include "event2/bufferevent.h"
#include "event2/event.h"
#include "event2/buffer.h"
#include "event2/listener.h"
#include "event2/event-config.h"
};

namespace core{

class Listener
{
public:
	Listener();
	~Listener();
	static int listen(const char * ip, unsigned port, network_cb cb, int sendBufMax, int recvBufMax, int proto);
	void setListenerID(int listenerID);
	void getListenAddr(String& ip, unsigned short& port);
	static void listener_cb(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *sa, 	int socklen, void *user_data);

private:

	int  m_listenerID;
	network_cb m_cb;
	int m_sendBufMax;
	int m_recvBufMax;
	int m_proto;
	evconnlistener *    m_evconnlister;
	core::String m_listenIP;
	unsigned short m_listenPort;

};
}

#endif //CORE_CORE_LISTENER_H__

