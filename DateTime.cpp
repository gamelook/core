#include "DateTime.hpp"
#include <memory.h>

namespace core {

Time::Time():
	hour(0),
	minute(0),
	second(0)
{

}

Time::Time(time_t t)
{
	struct tm * t_ = localtime(&t); 
	if(t_ != NULL)
	{
		this->hour   = t_->tm_hour;
		this->minute = t_->tm_min;
		this->second = t_->tm_sec;
	}
	else
	{
		this->hour   = 0;
		this->minute = 0;
		this->second = 0;

	}
}

Time::Time(const Time & t)
{
	this->hour   = t.hour;
	this->minute = t.minute;
	this->second = t.second;
}

Time::operator time_t()
{
	 struct tm t_;
	 memset(&t_,0,sizeof(t_));

	 t_.tm_hour = this->hour;
	 t_.tm_min  = this->minute;
	 t_.tm_sec  = this->second;

	 return mktime(&t_);
}

Date::Date():
	year(0),
	month(0),
	day(0)
{

}

Date::Date(time_t t)
{
	struct tm * t_ = localtime(&t); 
	if(t_ != NULL)
	{
		this->year  = t_->tm_year + 1900;
		this->month = t_->tm_mon + 1;
		this->day   = t_->tm_mday ;
	}
	else
	{
		this->year  = 0;
		this->month = 0;
		this->day   = 0;

	}

}

Date::Date(const Date & t)
{
	this->year  = t.year;
	this->month = t.month;
	this->day   = day;
}

Date::operator time_t()
{
	 struct tm t_;
	 memset(&t_,0,sizeof(t_));

	 t_.tm_year  = this->year - 1900;
	 t_.tm_mon   = this->month - 1;
	 t_.tm_mday  = this->day;

	 return mktime(&t_);
}

DateTime::DateTime()
{

}
DateTime::DateTime(time_t t)
{
	struct tm * t_ = localtime(&t); 
	if(t_ != NULL)
	{
		this->year   = t_->tm_year + 1900;
		this->month  = t_->tm_mon + 1;
		this->day    = t_->tm_mday;
		this->hour   = t_->tm_hour;
		this->minute = t_->tm_min;
		this->second = t_->tm_sec;
	}
	else
	{
		this->year   = 0;
		this->month  = 0;
		this->day    = 0;
		this->hour   = 0;
		this->minute = 0;
		this->second = 0;
	}
}
DateTime::DateTime(const DateTime & t)
{
	this->year   = t.year;
	this->month  = t.month;
	this->day    = t.day;
	this->hour   = t.hour;
	this->minute = t.minute;
	this->second = t.second;
}

DateTime::operator time_t()
{
	 struct tm t_;
	 memset(&t_,0,sizeof(t_));

	 t_.tm_year  = this->year - 1900;
	 t_.tm_mon   = this->month  -1;
	 t_.tm_mday  = this->day;
	 t_.tm_hour  = this->hour;
	 t_.tm_min   = this->minute;
	 t_.tm_sec   = this->second;

	 return mktime(&t_);
}

}