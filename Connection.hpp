#ifndef CORE_CORE_CONNECTION_H__
#define CORE_CORE_CONNECTION_H__

#include "typedef.hpp"
#include <string>

extern "C" {
#include "event2/bufferevent.h"
#include "event2/event.h"
#include "event2/buffer.h"
#include "event2/listener.h"
#include "event2/event-config.h"
};

namespace core{

union head{
	int size;
	char data[4];
};

class Connection:
	public Pool
{
public:
	Connection();
	Connection(bufferevent* bev, network_cb cb, int sendBufMax, int recvBufMax, int proto);
	~Connection();

	static int connect(const char * ip, unsigned port, network_cb cb, int sendBufMax, int recvBufMax, int proto);

	int send(char * buf, int size);
	void setConnectorID(int connectionID);
	bool isConnected();
	void getRemoteAddr(String& ip, unsigned short& port);
	void getLocalAddr(String& ip, unsigned short& port);
	void close();

	static void conn_eventcb(struct bufferevent *bev, short events, void *user_data);
	static void conn_readcb(struct bufferevent *bev, void *user_data);
	static void conn_writecb(struct bufferevent *bev, void *user_data);
	static void http_readcb(struct bufferevent *bev, void *user_data);
	static void http_writecb(struct bufferevent *bev, void *user_data);
	static void delay_close(int connectionID);
private:
	void getaddr();

private:
	int m_connectionID;
	int m_sendBufMax;
	int m_recvBufMax;
	int m_proto;
	String m_remoteIP;
	unsigned short m_remotePort;
	String m_localIP;
	unsigned short m_localPort;
	bool m_isConnected;
	bufferevent* m_bev;
	network_cb m_cb;

	char * m_buf;
	int      m_size;
	bool    m_header;

};


}
#endif //CORE_CORE_CONNECTION_H__
