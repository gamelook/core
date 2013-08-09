#ifndef __DATETIME_H__
#define __DATETIME_H__

#include <time.h>

namespace core{

class Time
{
public:
	unsigned char hour;
	unsigned char minute;
	unsigned char second;

public:
	Time();
	Time(time_t t);
	Time(const Time & t);
	operator time_t();


};

class Date
{
public:
	unsigned short year;
	unsigned char  month;
	unsigned char  day;

public:
	Date();
	Date(time_t t);
	Date(const Date & t);
	operator time_t();

};

class DateTime:
	public Date,
	public Time
{
public:
	DateTime();
	DateTime(time_t t);
	DateTime(const DateTime & t);
	operator time_t();

};

template <typename AR>
AR& operator >> (AR& ar, DateTime& data)
{
	ar << data.year;
	ar << data.month;
	ar << data.day;
	ar << data.hour;
	ar << data.minute;
	ar << data.second;
	return ar;
}

template <typename AR>
AR& operator << (AR& ar, const DateTime& data)
{
	ar >> data.year;
	ar >> data.month;
	ar >> data.day;
	ar >> data.hour;
	ar >> data.minute;
	ar >> data.second;
	return ar;
}

}
#endif //__DATETIME_H__
