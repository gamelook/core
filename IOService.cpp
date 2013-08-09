#include "IOService.hpp"
#include "Connection.hpp"
#include "Listener.hpp"
#include "Hash.hpp"
#include "Application.hpp"

#include <signal.h>

extern "C" {
#include "event2/bufferevent.h"
#include "event2/event.h"
#include "event2/buffer.h"
#include "event2/event_struct.h"
#include <event2/event-config.h>

};
#include <iostream>

namespace core {

class Timer
{
public:
	struct event timeout;
	int timeInterval;
	int repeat;
	int tid;
	TimerHandler * handler;
	int offset;

};

struct event_base * g_event_base = NULL;
Hash<Connection>  g_connections;
Hash<Listener>      g_listeners;
Hash<Timer>         g_timers;


struct event g_signal_int;


void signal_cb(evutil_socket_t fd, short e, void *arg)
{
	std::cout <<"exit\n";
	IOService::stop();
	
}



bool IOService::init()
{
#ifdef WIN32
	WSADATA wsa_data;
	WSAStartup(0x0201, &wsa_data);
#endif

	g_event_base = event_base_new();
	if (!g_event_base) {
		fprintf(stderr, "Could not initialize libevent!\n");
		return false;
	}

	event_assign(&g_signal_int, g_event_base, SIGINT, EV_SIGNAL|EV_PERSIST, signal_cb, NULL);

	event_add(&g_signal_int, NULL);

	return true;
}


Application * g_app = NULL;
void IOService::run(Application * app, int argc, char* argv[])
{
	g_app = app;
	if(g_app != NULL)
		g_app->onInit(argc, argv);
	 event_base_dispatch(g_event_base);
}

void 	exit_cb(evutil_socket_t fd, short event, void *arg)
{
	event_del((struct event*)arg);
	if(g_app != NULL)
		g_app->onExit();
	struct timeval tv;
	tv.tv_sec = 2;
	tv.tv_usec = 0;
	event_base_loopexit(g_event_base, &tv);
}

void IOService::stop()
{
	if(g_app != NULL)
		g_app->onSave();

	event_del(&g_signal_int);

	struct timeval tv;
	tv.tv_sec = 2;
	tv.tv_usec = 0;

	static struct event timeout;

	event_assign(&timeout, g_event_base, -1, EV_PERSIST, exit_cb, &timeout);
	event_add(&timeout, &tv);

}

void IOService::finit()
{
	g_connections.removeAll();
	g_listeners.removeAll();
	event_base_free(g_event_base);

}

int IOService::connect(const String& ip, unsigned port, network_cb cb, int sendBufMax, int recvBufMax, int proto)
{
	return connect(ip.c_str(), port, cb, sendBufMax, recvBufMax, proto);
}

int IOService::listen(const String& ip, unsigned port, network_cb cb, int sendBufMax, int recvBufMax, int proto)
{
	return listen(ip.c_str(), port, cb, sendBufMax, recvBufMax, proto);
}

int IOService::connect(const char * ip, unsigned port, network_cb cb, int sendBufMax, int recvBufMax, int proto)
{
	return Connection::connect(ip, port, cb, sendBufMax, recvBufMax, proto);
}

int IOService::listen(const char * ip, unsigned port, network_cb cb, int sendBufMax, int recvBufMax, int proto)
{
	return Listener::listen(ip, port, cb, sendBufMax, recvBufMax, proto);
}

int IOService::send(int connectionID, char * buf, int size)
{
	Connection * conn = g_connections.find(connectionID);
	if(conn != NULL && conn->isConnected())
	{
		return conn->send(buf, size);
	}
	return -1;
}

void IOService::getRemoteAddr(int connectionID, String& ip, unsigned short& port)
{
	Connection * conn = g_connections.find(connectionID);
	if(conn != NULL && conn->isConnected())
	{
		conn->getRemoteAddr(ip, port);
	}
}

void IOService::getLocalAddr(int connectionID, String& ip, unsigned short& port)
{
	Connection * conn = g_connections.find(connectionID);
	if(conn != NULL && conn->isConnected())
	{
		conn->getLocalAddr(ip, port);
	}
}

void IOService::getListenAddr(int listenerID, String& ip, unsigned short& port)
{
	Listener * list = g_listeners.find(listenerID);
	if(list != NULL)
	{
		list->getListenAddr(ip, port);
	}
}



void IOService::freeConnection(int connectionID)
{
	Connection * conn = g_connections.find(connectionID);
	if(conn != NULL)
	{
		conn->close();
	}

}

void IOService::freeListener(int listenerID)
{
	g_listeners.remove(listenerID);
}

void 	timeout_cb(evutil_socket_t fd, short event, void *arg)
{
	Timer * t = (Timer*)arg;
	t->handler->execute();
	--t->repeat;
	if(t->repeat > 0)
	{
		if(t->offset > 0)
		{
			event_del(&t->timeout);

			struct timeval tv;
			tv.tv_sec = t->timeInterval / 1000;
			tv.tv_usec = t->timeInterval % 1000 * 1000;
			event_add(&t->timeout, &tv);
		}
		
	}
	else
	{
		event_del(&t->timeout);
		delete t->handler;
		g_timers.remove(t->tid);
	}
}



int IOService::addTimer(TimerHandler* handler, int timeInterval , int repeat, int offset)
{
	Timer * t = new Timer();
	t->repeat = repeat;
	t->timeInterval = timeInterval;
	t->handler = handler;
	t->offset = offset;
	int tid = g_timers.add(t);
	t->tid = tid;
	
	event_assign(&t->timeout, g_event_base, -1, EV_PERSIST, timeout_cb, t);

	struct timeval tv;
	tv.tv_sec = offset + timeInterval / 1000;
	tv.tv_usec = timeInterval % 1000 * 1000;
	
	event_add(&t->timeout, &tv);
	return tid;
}

void IOService::removeTimer(int tid)
{
	Timer * t = g_timers.find(tid);
	if(t != NULL)
	{
		event_del(&t->timeout);
		delete t->handler;
	}
	g_timers.remove(tid);
}

int IOService::gettimeofday()
{
	struct timeval curTime;

	evutil_gettimeofday(&curTime, NULL);
	return curTime.tv_sec;
}

}

