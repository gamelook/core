template <typename T>
class TimerHandlerT;

template <typename R>
class TimerHandlerT<R ()>:
	public TimerHandler
{
public:
	typedef R (*FUNC)();
	TimerHandlerT(FUNC func):
		m_func(func)
	{
	}

	virtual void execute()
	{
		m_func();
	}

private:
	FUNC m_func;
};

template <typename R>
TimerHandler* bind(R(*func)())
{
	 return new TimerHandlerT<R()>(func);
}

template<typename R, typename P1>
class TimerHandlerT<R (P1)>:
	public TimerHandler
{
public:
	typedef R(*FUNC)(P1);
	TimerHandlerT(FUNC func,const P1& p1):
		m_func(func),
		m_p1(p1)
	{
	}

	virtual void execute()
	{
		m_func(m_p1);
	}

private:
	FUNC m_func;
	P1 m_p1;

};

template <typename R, typename P1>
TimerHandler* bind(R (*func)(P1),const P1& p1)
{
	return new TimerHandlerT<R (P1)>(func,p1);
}

template<typename R, typename P1,typename P2>
class TimerHandlerT<R (P1,P2)>:
	public TimerHandler
{
public:
	typedef R(*FUNC)(P1,P2);
	TimerHandlerT(FUNC func,const P1& p1,const P2& p2):
		m_func(func),
		m_p1(p1),
		m_p2(p2)
	{
	}

	virtual void execute()
	{
		m_func(m_p1,m_p2);
	}

private:
	FUNC m_func;
	P1 m_p1;
	P2 m_p2;

};

template <typename R, typename P1,typename P2>
TimerHandler* bind(R (*func)(P1,P2),const P1& p1,const P2& p2)
{
	return new TimerHandlerT<R (P1,P2)>(func,p1,p2);
}

template <typename R, typename C>
class TimerHandlerT<R (C::*)()>:
	public TimerHandler
{
public:
	typedef R (C::*FUNC)();
	TimerHandlerT(FUNC func,C* obj):
		m_func(func),
		m_obj(obj)
	{
	}

	virtual void execute()
	{
		(m_obj->*m_func)();
	}

private:
	FUNC m_func;
	C*   m_obj;
};

template <typename R, typename C>
TimerHandler* bind(R(C::*func)(),C* obj)
{
	 return new TimerHandlerT<R(C::*)()>(func,obj);
}

template<typename R, typename C, typename P1>
class TimerHandlerT<R (C::*)(P1)>:
	public TimerHandler
{
public:
	typedef R(C::*FUNC)(P1);
	TimerHandlerT(FUNC func, C* obj, const P1& p1):
	m_func(func),
	m_obj(obj),
	m_p1(p1)
	{
	}

	virtual void execute()
	{
		(m_obj->*m_func)(m_p1);
	}

private:
	FUNC m_func;
	C*   m_obj;
	P1 m_p1;

};

template <typename R, typename C, typename P1>
TimerHandler* bind(R (C::*func)(P1),C* obj,const P1& p1)
{
	return new TimerHandlerT<R (C::*)(P1)>(func,obj,p1);
}
template<typename R, typename C, typename P1,typename P2>
class TimerHandlerT<R (C::*)(P1,P2)>:
	public TimerHandler
{
public:
	typedef R(C::*FUNC)(P1,P2);
	TimerHandlerT(FUNC func, C* obj, const P1& p1,const P2& p2):
	m_func(func),
	m_obj(obj),
	m_p1(p1),
	m_p2(p2)
	{
	}

	virtual void execute()
	{
		(m_obj->*m_func)(m_p1,m_p2);
	}

private:
	FUNC m_func;
	C*   m_obj;
	P1 m_p1;
	P2 m_p2;

};

template <typename R, typename C, typename P1,typename P2>
TimerHandler* bind(R (C::*func)(P1,P2),C* obj,const P1& p1,const P2& p2)
{
	return new TimerHandlerT<R (C::*)(P1,P2)>(func,obj,p1,p2);
}

