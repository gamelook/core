#ifndef CORE_CORE_TIMERHANDLER_H__
#define CORE_CORE_TIMERHANDLER_H__

#include "typedef.hpp"

namespace core{

class TimerHandler:
	public Pool
{
public:
	TimerHandler(){}
	virtual ~TimerHandler(){}
	virtual void execute() = 0;
};

#include "TimerHandlerT.hpp"

}
#endif //CORE_CORE_TIMERHANDLER_H__

