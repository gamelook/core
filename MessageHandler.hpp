#ifndef CORE_CORE_MESSAGEHANDLER_H__
#define CORE_CORE_MESSAGEHANDLER_H__

#include "IStream.hpp"

namespace core{

class MessageHandler:
	public Pool
{
public:
	MessageHandler(){}
	virtual ~MessageHandler(){}
	virtual void execute(int connectionID, char * buf, int size){}
	virtual void execute(int connectionID, int userID, char * buf, int size){}
};


template <typename T>
class MessageHandlerT;

template <typename T>
class MessageHandlerT<void (int, T&)>:
	public MessageHandler
{
public:
	MessageHandlerT(void (*func)(int, T&));
	virtual ~MessageHandlerT();

	virtual void execute(int connectionID, char * buf, int size);

private:
	void (*m_func)(int, T&);
	
};

template <typename T>
inline MessageHandlerT<void (int, T&)>::MessageHandlerT(void (*func)(int, T&)):
	m_func(func)
{

}

template <typename T>
inline MessageHandlerT<void (int, T&)>::~MessageHandlerT()
{

}

template <typename T>
inline void MessageHandlerT<void (int, T&)>::execute(int connectionID, char * buf, int size)
{
	IStream is(buf, size);
	T       v;
	is >> v;
	m_func(connectionID, v);
}


template <typename T>
class MessageHandlerT<void (int, int, T&)>:
	public MessageHandler
{
public:
	MessageHandlerT(void (*func)(int, int, T&));
	virtual ~MessageHandlerT();

	virtual void execute(int connectionID, int userID, char * buf, int size);

private:
	void (*m_func)(int, int, T&);

};

template <typename T>
inline MessageHandlerT<void (int, int, T&)>::MessageHandlerT(void (*func)(int, int, T&)):
m_func(func)
{

}

template <typename T>
inline MessageHandlerT<void (int, int, T&)>::~MessageHandlerT()
{

}

template <typename T>
inline void MessageHandlerT<void (int, int, T&)>::execute(int connectionID, int userID, char * buf, int size)
{
	IStream is(buf, size);
	T       v;
	is >> v;
	m_func(connectionID, userID, v);
}



template <typename T>
class MessageHandlerT<void (int, T&, IStream&)>:
	public MessageHandler
{
public:
	MessageHandlerT(void (*func)(int, T&, IStream&));
	virtual ~MessageHandlerT();

	virtual void execute(int connectionID, char * buf, int size);

private:
	void (*m_func)(int, T&, IStream&);

};

template <typename T>
inline MessageHandlerT<void (int, T&, IStream&)>::MessageHandlerT(void (*func)(int, T&, IStream&)):
m_func(func)
{

}

template <typename T>
inline MessageHandlerT<void (int, T&, IStream&)>::~MessageHandlerT()
{

}

template <typename T>
inline void MessageHandlerT<void (int, T&, IStream&)>::execute(int connectionID, char * buf, int size)
{
	IStream is(buf, size);
	T       v;
	is >> v;
	m_func(connectionID, v, is);
}

template <typename T>
class MessageHandlerT<void (int, int, T&, IStream&)>:
	public MessageHandler
{
public:
	MessageHandlerT(void (*func)(int, int, T&, IStream&));
	virtual ~MessageHandlerT();

	virtual void execute(int connectionID, int userID, char * buf, int size);

private:
	void (*m_func)(int, int, T&, IStream&);

};

template <typename T>
inline MessageHandlerT<void (int, int, T&, IStream&)>::MessageHandlerT(void (*func)(int, int, T&, IStream&)):
m_func(func)
{

}

template <typename T>
inline MessageHandlerT<void (int, int, T&, IStream&)>::~MessageHandlerT()
{

}

template <typename T>
inline void MessageHandlerT<void (int, int, T&, IStream&)>::execute(int connectionID, int userID, char * buf, int size)
{
	IStream is(buf, size);
	T       v;
	is >> v;
	m_func(connectionID, userID, v, is);
}


template <>
class MessageHandlerT<void (int, char *, int)>:
	public MessageHandler
{
public:
	MessageHandlerT(void (*func)(int, char *, int)):
		m_func(func)
	{
	}
	virtual ~MessageHandlerT()
	{

	}

	virtual void execute(int connectionID, char * buf, int size)
	{
		m_func(connectionID, buf, size);
	}

private:
	void (*m_func)(int, char *, int);
};

template <>
class MessageHandlerT<void (int, int, char *, int)>:
	public MessageHandler
{
public:
	MessageHandlerT(void (*func)(int, int, char *, int)):
	  m_func(func)
	  {
	  }
	  virtual ~MessageHandlerT()
	  {

	  }

	  virtual void execute(int connectionID, int userID, char * buf, int size)
	  {
		  m_func(connectionID, userID, buf, size);
	  }

private:
	void (*m_func)(int, int, char *, int);
};
}

#endif //CORE_CORE_MESSAGEHANDLER_H__

