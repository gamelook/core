#include "Listener.hpp"
#include "Connection.hpp"
#include "Hash.hpp"

#ifndef WIN32
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#endif

namespace core {

extern struct event_base * g_event_base;
extern Hash<Listener> g_listeners;
extern Hash<Connection>  g_connections;

Listener::Listener()
{

}

Listener::~Listener()
{

}

int Listener::listen(const char *ip, unsigned port, network_cb cb, int sendBufMax, int recvBufMax, int proto)
{

	Listener * listener = new Listener();

	listener->m_cb = cb;
	listener->m_sendBufMax = sendBufMax;
	listener->m_recvBufMax = recvBufMax;
	listener->m_proto = proto;
	listener->m_listenerID = g_listeners.add(listener);
	

	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(ip);

	listener->m_evconnlister = evconnlistener_new_bind(g_event_base, listener_cb, listener,
		LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE, 1024,
		(struct sockaddr*)&sin,
		sizeof(sin));

	if (!listener->m_evconnlister) {
		return -1;
	}
	
	evutil_socket_t fd = evconnlistener_get_fd(listener->m_evconnlister);

	struct sockaddr_in localaddr;
	int local_len = sizeof(localaddr);
	getsockname(fd, (struct sockaddr *)&localaddr, &local_len);

	listener->m_listenIP = inet_ntoa(localaddr.sin_addr);
	listener->m_listenPort = ntohs(localaddr.sin_port);

	return listener->m_listenerID;
}

void Listener::listener_cb(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *sa, 	int socklen, void *user_data)
{
	Listener * listen = (Listener*) user_data;

	bufferevent * bev = bufferevent_socket_new(g_event_base, fd, BEV_OPT_CLOSE_ON_FREE);

	Connection * conn = new Connection(bev, listen->m_cb, listen->m_sendBufMax, listen->m_recvBufMax, listen->m_proto);
	int connID = g_connections.add(conn);
	conn->setConnectorID(connID);

	listen->m_cb(0, connID, NULL, 0);
	if(!conn->isConnected())
	{
		listen->m_cb(2, connID, NULL, 0);
		g_connections.remove(connID);
	}
}

void Listener::getListenAddr(String& ip, unsigned short& port)
{
	ip = m_listenIP;
	port = m_listenPort;
}

void Listener::setListenerID(int listenerID)
{
	m_listenerID = listenerID;
}

}

