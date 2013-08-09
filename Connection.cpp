#include "Connection.hpp"
#include "Hash.hpp"
#include <iostream>
#include "IOService.hpp"

namespace core {

extern struct event_base * g_event_base;
extern Hash<Connection> g_connections;

Connection::Connection():
	m_bev(NULL),
	m_buf(NULL),
	m_size(0),
	m_header(true),
	m_isConnected(false),
	m_connectionID(-1)
{

}

Connection::Connection(bufferevent* bev, network_cb cb, int sendBufMax, int recvBufMax, int proto):
	m_bev(bev),
	m_cb(cb),
	m_sendBufMax(sendBufMax),
	m_recvBufMax(recvBufMax),
	m_proto(proto),
	m_header(true),
	m_size(0),
	m_isConnected(true),
	m_connectionID(-1)
{
	bufferevent_setcb(m_bev, Connection::conn_readcb, Connection::conn_writecb, Connection::conn_eventcb, this);
	bufferevent_enable(m_bev, EV_WRITE|EV_READ);
	m_buf = new char[recvBufMax];
	getaddr();
}

Connection::~Connection()
{
	if(m_bev != NULL)
	{
		bufferevent_free(m_bev);
		m_bev = NULL;
	}

	if(m_buf != NULL)
		delete [] m_buf;
	
}

int Connection::connect(const char * ip, unsigned port, network_cb cb, int sendBufMax, int recvBufMax, int proto)
{
	Connection * conn = new Connection();
	conn->m_connectionID = g_connections.add(conn);
	conn->m_bev = bufferevent_socket_new(g_event_base, -1, BEV_OPT_CLOSE_ON_FREE|BEV_OPT_DEFER_CALLBACKS);
	conn->m_cb = cb;
	conn->m_sendBufMax = sendBufMax;
	conn->m_recvBufMax = recvBufMax;
	conn->m_proto = proto;
	conn->m_remoteIP = ip;
	conn->m_remotePort = port;
	conn->m_buf = new char[recvBufMax];

	bufferevent_setcb(conn->m_bev, NULL, NULL, conn_eventcb, conn);
	bufferevent_enable(conn->m_bev, EV_WRITE|EV_READ);
	int ret = bufferevent_socket_connect_hostname(conn->m_bev, NULL, AF_INET, ip, port);
	if(ret == 0)
		return conn->m_connectionID;
	else
		return -1;
}

int Connection::send(char * buf, int size)
{
	if(m_isConnected)
		return bufferevent_write(m_bev, buf, size);
	return -1;
}

void Connection::conn_eventcb(struct bufferevent *bev, short events, void *user_data)
{
	Connection * conn = (Connection*)user_data;

	if(BEV_EVENT_CONNECTED & events)
	{
		bufferevent_setcb(conn->m_bev, Connection::conn_readcb, Connection::conn_writecb, Connection::conn_eventcb, conn);
		bufferevent_enable(conn->m_bev, EV_WRITE|EV_READ);
		conn->m_isConnected = true;
		conn->m_header = true;
		conn->getaddr();

		conn->m_cb(0, conn->m_connectionID, NULL, 0);
				
	}
	else if(BEV_EVENT_ERROR & events)
	{
		conn->m_isConnected = false;
		conn->m_cb(3, -1, (char*)conn->m_remoteIP.c_str(), conn->m_remotePort);
		g_connections.remove(conn->m_connectionID);
	}
	else
	{
		conn->m_isConnected = false;
		conn->m_cb(2, conn->m_connectionID, NULL, 0);
		g_connections.remove(conn->m_connectionID);
	}

}


void Connection::conn_readcb(struct bufferevent *bev, void *user_data)
{
	Connection * conn = (Connection*)user_data;

	for(;;)
	{


		struct evbuffer * input = bufferevent_get_input(conn->m_bev);
		int length = evbuffer_get_length(input);
	
		if(conn->m_header)
		{
			if(length < sizeof(conn->m_size))
			{
				return;
			}
			else
			{
				bufferevent_read(conn->m_bev, &conn->m_size, sizeof(conn->m_size));
				conn->m_header = false;
				if(conn->m_size > conn->m_recvBufMax)
				{
					conn->m_isConnected = false;
					conn->m_cb(4, conn->m_connectionID, NULL, 0);
					g_connections.remove(conn->m_connectionID);
					return;
				}
			}
		}
		else
		{
			if(length < conn->m_size)
			{
				return;
				
			}
			else
			{
				bufferevent_read(conn->m_bev, conn->m_buf, conn->m_size);
				conn->m_header = true;
				conn->m_cb(1, conn->m_connectionID, conn->m_buf, conn->m_size);
				if(conn->m_isConnected == false)
				{
					return;
				}
			}
		}
	}
}

void Connection::conn_writecb(struct bufferevent *bev, void *user_data)
{

}

void Connection::http_readcb(struct bufferevent *bev, void *user_data)
{
	Connection * conn = (Connection*)user_data;

	for(;;)
	{
		struct evbuffer * input = bufferevent_get_input(conn->m_bev);
		int length = evbuffer_get_length(input);

		if(conn->m_header)
		{
			if(length < sizeof(conn->m_size))
			{
				return;
			}
			else
			{
				bufferevent_read(conn->m_bev, &conn->m_size, sizeof(conn->m_size));
				conn->m_header = false;
				if(conn->m_size > conn->m_recvBufMax)
				{
					conn->m_cb(3, conn->m_connectionID, NULL, 0);
					g_connections.remove(conn->m_connectionID);
				}
			}
		}
		else
		{
			if(length < conn->m_size)
			{
				return;

			}
			else
			{
				bufferevent_read(conn->m_bev, conn->m_buf, conn->m_size);
				conn->m_cb(1, conn->m_connectionID, conn->m_buf, conn->m_size);
				conn->m_header = true;
			}
		}
	}
}

void Connection::http_writecb(struct bufferevent *bev, void *user_data)
{

}

void Connection::setConnectorID(int connectionID)
{
	m_connectionID = connectionID;
}

bool Connection::isConnected()
{
	return m_isConnected;
}

void Connection::getRemoteAddr(String& ip, unsigned short& port)
{
	ip = m_remoteIP;
	port = m_remotePort;

}

void Connection::getLocalAddr(String& ip, unsigned short& port)
{
	ip = m_localIP;
	port = m_localPort;
}

void Connection::delay_close(int connectionID)
{
	Connection * conn = g_connections.find(connectionID);
	if(conn != NULL)
	{
		conn->m_cb(2, connectionID, NULL, 0);
		g_connections.remove(connectionID);
	}
}

void Connection::close()
{
	bufferevent_disable(m_bev, EV_READ);
	m_isConnected = false;
	IOService::addTimer(bind(delay_close, m_connectionID), 1);
}






void Connection::getaddr()
{
	evutil_socket_t fd = bufferevent_getfd(m_bev);

	struct sockaddr_in localaddr;
	struct sockaddr_in remoteaddr;
	int local_len = sizeof(localaddr);
	int remote_len = sizeof(remoteaddr);
	getsockname(fd, (struct sockaddr *)&localaddr, &local_len);
	getpeername(fd, (struct sockaddr *)&remoteaddr, &remote_len);

	m_localIP = inet_ntoa(localaddr.sin_addr);
	m_remoteIP = inet_ntoa(remoteaddr.sin_addr);
	m_localPort = ntohs(localaddr.sin_port);
	m_remotePort = ntohs(remoteaddr.sin_port);
}

}

