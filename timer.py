
def genGlobalHandler(n):
	s = oneGlobalHandler0()
	for i in range(1,n):
		s += oneGlobalHandler(i)
	return s
	
def oneGlobalHandler(i):
	s = "template<typename R, %s>\n"
	s += "class TimerHandlerT<R (%s)>:\n"
	s += "\tpublic TimerHandler\n"
	s += "{\n"
	s += "public:\n"
	s += "\ttypedef R(*FUNC)(%s);\n"
	s += "\tTimerHandlerT(FUNC func,%s):\n"
	s += "\t\tm_func(func),\n%s\n"
	s += "\t{\n"
	s += "\t}\n\n"
	s += "\tvirtual void execute()\n"
	s += "\t{\n"
	s += "\t\tm_func(%s);\n"
#	s += "\t\treturn true;\n"
	s += "\t}\n\n"
	s += "private:\n"
	s += "\tFUNC m_func;\n"
	s += "%s\n"
	s += "};\n\n"
	s += "template <typename R, %s>\n"
	s += "TimerHandler* bind(R (*func)(%s),%s)\n"
	s += "{\n"
	s += "\treturn new TimerHandlerT<R (%s)>(func,%s);\n"
	s += "}\n\n"
	typename_P1=range(i)
	P1=range(i)
	constP1=range(i)
	m_p1_p1=range(i)
	m_p1=range(i)
	P1_p1=""
	p1=range(i)	
	for n in range(1,i+1):
		typename_P1[n-1]="typename P%s" % n
		P1[n-1]="P%s" % n
		constP1[n-1]="const P%s& p%s" % (n,n)
		m_p1_p1[n-1]="\t\tm_p%s(p%s)" % (n,n)
		m_p1[n-1]="m_p%s" % n
		P1_p1 += "\tP%s m_p%s;\n" % (n,n)
		p1[n-1]="p%s" % n
	s = s % (",".join(typename_P1),",".join(P1),\
	",".join(P1),",".join(constP1),",\n".join(m_p1_p1),\
	",".join(m_p1),P1_p1,",".join(typename_P1),\
	",".join(P1),",".join(constP1),",".join(P1),",".join(p1))
	return s
	

def oneGlobalHandler0():
	s = "template <typename R>\n"
	s += "class TimerHandlerT<R ()>:\n"
	s += "\tpublic TimerHandler\n"
	s += "{\n"
	s += "public:\n"
	s += "\ttypedef R (*FUNC)();\n"
	s += "\tTimerHandlerT(FUNC func):\n"
	s += "\t\tm_func(func)\n"
	s += "\t{\n"
	s += "\t}\n\n"
	s += "\tvirtual void execute()\n"
	s += "\t{\n"
	s += "\t\tm_func();\n"
#	s += "\t\treturn true;\n"
	s += "\t}\n\n"
	s += "private:\n"
	s += "\tFUNC m_func;\n"
	s += "};\n\n"
	s += "template <typename R>\n"
	s += "TimerHandler* bind(R(*func)())\n"
	s += "{\n"
	s += "\t return new TimerHandlerT<R()>(func);\n"
	s += "}\n\n"
	return s;
	

def genClassHandler(n):
	s = oneClassHandler0()
	for i in range(1,n):
		s += oneClassHandler(i)
	return s

def oneClassHandler(i):
	s = "template<typename R, typename C, %s>\n"
	s += "class TimerHandlerT<R (C::*)(%s)>:\n"
	s += "\tpublic TimerHandler\n"
	s += "{\n"
	s += "public:\n"
	s += "\ttypedef R(C::*FUNC)(%s);\n"
	s += "\tTimerHandlerT(FUNC func, C* obj, %s):\n"
	s += "\tm_func(func),\n"
	s += "\tm_obj(obj),\n%s\n"
	s += "\t{\n"
	s += "\t}\n\n"
	s += "\tvirtual void execute()\n"
	s += "\t{\n"
	s += "\t\t(m_obj->*m_func)(%s);\n"
#	s += "\t\treturn true;\n"
	s += "\t}\n\n"
	s += "private:\n"
	s += "\tFUNC m_func;\n"
	s += "\tC*   m_obj;\n"
	s += "%s\n"
	s += "};\n\n"
	s += "template <typename R, typename C, %s>\n"
	s += "TimerHandler* bind(R (C::*func)(%s),C* obj,%s)\n"
	s += "{\n"
	s += "\treturn new TimerHandlerT<R (C::*)(%s)>(func,obj,%s);\n"
	s += "}\n"
	typename_P1=range(i)
	P1=range(i)
	constP1=range(i)
	m_p1_p1=range(i)
	m_p1=range(i)
	P1_p1=""
	p1=range(i)	
	for n in range(1,i+1):
		typename_P1[n-1]="typename P%s" % n
		P1[n-1]="P%s" % n
		constP1[n-1]="const P%s& p%s" % (n,n)
		m_p1_p1[n-1]="\tm_p%s(p%s)" % (n,n)
		m_p1[n-1]="m_p%s" % n
		P1_p1 += "\tP%s m_p%s;\n" % (n,n)
		p1[n-1]="p%s" % n
	s = s % (",".join(typename_P1),",".join(P1),\
	",".join(P1),",".join(constP1),",\n".join(m_p1_p1),\
	",".join(m_p1),P1_p1,",".join(typename_P1),\
	",".join(P1),",".join(constP1),",".join(P1),",".join(p1))
	return s
	
def oneClassHandler0():
	s = "template <typename R, typename C>\n"
	s += "class TimerHandlerT<R (C::*)()>:\n"
	s += "\tpublic TimerHandler\n"
	s += "{\n"
	s += "public:\n"
	s += "\ttypedef R (C::*FUNC)();\n"
	s += "\tTimerHandlerT(FUNC func,C* obj):\n"
	s += "\t\tm_func(func),\n"
	s += "\t\tm_obj(obj)\n"
	s += "\t{\n"
	s += "\t}\n\n"
	s += "\tvirtual void execute()\n"
	s += "\t{\n"
	s += "\t\t(m_obj->*m_func)();\n"
#	s += "\t\treturn true;\n"
	s += "\t}\n\n"
	s += "private:\n"
	s += "\tFUNC m_func;\n"
	s += "\tC*   m_obj;\n"
	s += "};\n\n"
	s += "template <typename R, typename C>\n"
	s += "TimerHandler* bind(R(C::*func)(),C* obj)\n"
	s += "{\n"
	s += "\t return new TimerHandlerT<R(C::*)()>(func,obj);\n"
	s += "}\n\n"
	return s;	
	
s  = "template <typename T>\n"
s += "class TimerHandlerT;\n\n"
s += genGlobalHandler(3);
s += genClassHandler(3);

f = open("TimerHandlerT.hpp",'w')
f.write(s)
f.close()