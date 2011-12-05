#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE       // See feature_test_macros(7)
#endif

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstring>
#include <climits>

#include "datetime.hpp"

// 
// The maximum size of time_t is determined experimental. One would expect 
// that 0x1 << 64 is OK, but it breaks asctime() and others.
// 
#if defined(__x86_64__)     // 64-bit
# define TIME_T_MAX  ((time_t)0x1 << 55)    // Approx.
# define TIME_T_I386 ((time_t)0x1 << 31) 
#else                       // 32-bit
# define TIME_T_MAX  ((time_t)0x1 << 31)
#endif

// 
// The recognized format strings. See strptime(3) for more info.
// 
const char * DateTime::Formats[] = { 
	// 
	// Custom formats:
	// 
	"%x %X",                  // Locale specific format.
	"%x",                     // Locale specific format (date only).
	"%X",                     // Locale specific format (time only).
	"%Y-%m-%d",               // ISO 8601 time format.
	"%H:%M:%S",               // ISO 8601 time format.
	"%a, %d %b %Y %T %z",     // RFC 8222-compliant.
	"%a, %d %b %y %T %z",     // RFC 822-compliant.
	"%a %h %e %H:%M:%S %Y",   // Format of asctime (i.e. Wed Jun 30 21:49:08 1993).
	"%Y-%m-%d %H:%M:%S",      // Common european date/time.
	"%m/%d/%y",               // American date.
	"%y-%m-%d",               // Short date format.
	// 
	// Standard formats:
	// 
	"%A",     // The weekday name according to the current locale.
	"%F",     // Equivalent to %Y-%m-%d, the ISO 8601 date format.
	"%T",     // Equivalent to %H:%M:%S.
	"%F %T",  // Common european representation of full date/time.
	"%a",     // The weekday name according to the current locale, in abbreviated form or the full name. Same as %A.
	"%b",
	"%B", 
	"%h",     // The month name according to the current locale, in abbreviated form or the full name.
	"%c",     // The date and time representation for the current locale.
	"%C",     // The century number (0-99).
	"%d",
	"%e",     // The day of month (1-31).
	"%D",     // Equivalent to %m/%d/%y. (This is the American style date, very confusing to non-Americans, especially since %d/%m/%y is widely used in Europe. The ISO 8601 standard format is %Y-%m-%d.)
	"%H",     // The hour (0-23).
	"%I",     // The hour on a 12-hour clock (1-12).
	"%j",     // The day number in the year (1-366).
	"%m",     // The month number (1-12).
	"%M",     // The minute (0-59).
	"%n",     // Arbitrary whitespace.
	"%p",     // The locale's equivalent of AM or PM. (Note: there may be none.)
	"%r",     // The 12-hour clock time (using the locale's AM or PM). In the POSIX locale equivalent to %I:%M:%S %p. If t_fmt_ampm is empty in the LC_TIME part of the current locale then the behavior is undefined.
	"%R",     // Equivalent to %H:%M.
	"%S",     // The second (0-60; 60 may occur for leap seconds; earlier also 61 was allowed).
	"%t",     // Arbitrary whitespace.
	"%T",     // Equivalent to %H:%M:%S.
	"%U",     // The week number with Sunday the first day of the week (0-53). The first Sunday of January is the first day of week 1.
	"%w",     // The weekday number (0-6) with Sunday = 0.
	"%W",     // The week number with Monday the first day of the week (0-53). The first Monday of January is the first day of week 1.
	"%x",     // The date, using the locale's date format.
	"%X",     // The time, using the locale's time format.
	"%y",     // The  year  within  century  (0-99).  When a century is not otherwise specified, values in the range 69-99 refer to years in the twentieth century (1969-1999); values in the range 00-68 refer to years in the twenty-first century (2000-2068).
	"%Y",     // The year, including century (for example, 1991).
	// 
	// Alternative locale-dependent:
	// 
	"%Ec",    // The locale's alternative date and time representation.
	"%EC",    // The name of the base year (period) in the locale's alternative representation.
	"%Ex",    // The locale's alternative date representation.
	"%EX",    // The locale's alternative time representation.
	"%Ey",    // The offset from %EC (year only) in the locale's alternative representation.
	"%EY",    // The full alternative year representation.
	"%Od",
	"%Oe",    // The day of the month using the locale's alternative numeric symbols; leading zeros are permitted but not required.
	"%OH",    // The hour (24-hour clock) using the locale's alternative numeric symbols.
	"%OI",    // The hour (12-hour clock) using the locale's alternative numeric symbols.
	"%Om",    // The month using the locale's alternative numeric symbols.
	"%OM",    // The minutes using the locale's alternative numeric symbols.
	"%OS",    // The seconds using the locale's alternative numeric symbols.
	"%OU",    // The week number of the year (Sunday as the first day of the week) using the locale's alternative numeric symbols.
	"%Ow",    // The number of the weekday (Sunday=0) using the locale's alternative numeric symbols.
	"%OW",    // The week number of the year (Monday as the first day of the week) using the locale's alternative numeric symbols.
	"%Oy",    // The year (offset from %C) using the locale's alternative numeric symbols.
	0
};

const char * DateTime::fmt = DateTime::Formats[DateTime::European];

DateTime DateTime::min = DateTime();
// DateTime DateTime::max = DateTime((time_t)(UINT_MAX));
// DateTime DateTime::max = DateTime((time_t)(1 << sizeof(time_t)));
// DateTime DateTime::max = DateTime((time_t)(time_t(-1)));
// DateTime DateTime::max = DateTime((time_t)(LONG_MAX));
DateTime DateTime::max = DateTime(TIME_T_MAX);

std::ostream & operator <<(std::ostream &out, const DateTime &dt) 
{	
	return out << dt.Write();
}

std::istream & operator >>(std::istream &in, DateTime &dt) 
{	
	std::string str;
	std::getline(in, str, '\n');
	dt = DateTime(str);
	return in;
}

DateTime::Data::Data()
{
	memset(&tm, 0, sizeof(std::tm));
	tm.tm_mon  = MONTH_SHIFT;
	tm.tm_mday = DAY_SHIFT;
}

bool DateTime::Data::Set(const char *str, const char *fmt)
{
	char *p = strptime(str, fmt, &tm);
	return p != 0 && *p == '\0';
}

DateTime::DateTime()
{
}

DateTime::DateTime(std::time_t t)
{
	d.tm = *(std::localtime(&t));
}

DateTime::DateTime(int year, int month, int mday, int hour, int min, int sec, int isdst, bool normalize)
{
	d.tm.tm_year = year - YEAR_SHIFT;
	d.tm.tm_mon = month - MONTH_SHIFT;
	d.tm.tm_mday = mday;
	d.tm.tm_hour = hour;
	d.tm.tm_min = min;
	d.tm.tm_sec = sec;
	d.tm.tm_isdst = isdst;
	
	if(d.tm.tm_year < 0) {
		d.tm.tm_year = year;
		normalize = false;
	}
	if(d.tm.tm_mon < 0) {
		d.tm.tm_mon = month;
		normalize = false;
	}
	
	if(normalize && std::mktime(&d.tm) < 0) {
		throw Exception();
	}
}

DateTime::DateTime(const std::string &str)
{
	if(!d.Set(str.c_str(), fmt)) {
		throw Exception();
	}
}

DateTime::DateTime(const std::string &str, const char *fmt)
{
	if(!d.Set(str.c_str(), fmt)) {
		throw Exception();
	}
}

DateTime::DateTime(const std::string &str, Format fmt)
{
	if(!d.Set(str.c_str(), Formats[fmt])) {
		throw Exception();
	}
}

DateTime::DateTime(const char *str)
{
	Read(str);
}

DateTime DateTime::Now()
{
	return DateTime(time(0));
}

DateTime DateTime::Epoch()
{
	return DateTime(time_t(0));
}

#if defined(__x86_64__)
DateTime DateTime::I386()
{
	return DateTime(time_t(TIME_T_I386));
}
#endif

DateTime & DateTime::Normalize()
{
	if(mktime(&d.tm) < 0) {
		throw Exception();
	}
	return *this;
}

void DateTime::Read(const char *str)
{
	for(const char **fmt = Formats; *fmt; ++fmt) {
		if(d.Set(str, *fmt)) {
			return;
		}
	}
	throw Exception();
}

std::string DateTime::Write(const char *fmt) const
{
	char buff[200];
	strftime(buff, sizeof(buff), fmt, &d.tm);
	return buff;
}

#if defined(__DATETIME_MUTABLE__)
DateTime & DateTime::operator +=(const DateTime &r)
{
	d.tm.tm_year += r.d.tm.tm_year;
	d.tm.tm_mon  += r.d.tm.tm_mon;
	d.tm.tm_mday += r.d.tm.tm_mday;
	d.tm.tm_hour += r.d.tm.tm_hour;
	d.tm.tm_min  += r.d.tm.tm_min;
	d.tm.tm_sec  += r.d.tm.tm_sec;
	
	return *this;
}

DateTime & DateTime::operator -=(const DateTime &r)
{
	d.tm.tm_year -= r.d.tm.tm_year;
	d.tm.tm_mon  -= r.d.tm.tm_mon;
	d.tm.tm_mday -= r.d.tm.tm_mday;
	d.tm.tm_hour -= r.d.tm.tm_hour;
	d.tm.tm_min  -= r.d.tm.tm_min;
	d.tm.tm_sec  -= r.d.tm.tm_sec;
	
	return *this;
}
#endif
	
bool operator ==(const DateTime &l, const DateTime &r)
{
	return ((l.d.tm.tm_year == r.d.tm.tm_year) &&
		(l.d.tm.tm_mon  == r.d.tm.tm_mon) &&
		(l.d.tm.tm_mday == r.d.tm.tm_mday) &&
		(l.d.tm.tm_hour == r.d.tm.tm_hour) &&
		(l.d.tm.tm_min  == r.d.tm.tm_min) &&
		(l.d.tm.tm_sec  == r.d.tm.tm_sec));
}

bool operator !=(const DateTime &l, const DateTime &r)
{
	return ! operator==(l, r);
}

bool operator >(const DateTime &l, const DateTime &r)
{
	return ((l.d.tm.tm_year > r.d.tm.tm_year) &&
		(l.d.tm.tm_mon  > r.d.tm.tm_mon) &&
		(l.d.tm.tm_mday > r.d.tm.tm_mday) &&
		(l.d.tm.tm_hour > r.d.tm.tm_hour) &&
		(l.d.tm.tm_min  > r.d.tm.tm_min) &&
		(l.d.tm.tm_sec  > r.d.tm.tm_sec));
}

bool operator <(const DateTime &l, const DateTime &r)
{
	return ((l.d.tm.tm_year < r.d.tm.tm_year) &&
		(l.d.tm.tm_mon  < r.d.tm.tm_mon) &&
		(l.d.tm.tm_mday < r.d.tm.tm_mday) &&
		(l.d.tm.tm_hour < r.d.tm.tm_hour) &&
		(l.d.tm.tm_min  < r.d.tm.tm_min) &&
		(l.d.tm.tm_sec  < r.d.tm.tm_sec));
}

// 
// Example/test program:
// Compile: g++ -Wall -W -O -g -D__DATETIME_CPP_MAIN__=1 -D__DATETIME_FORMAT_ASCTIME__=1 -D__DATETIME_MUTABLE__=1 datetime.cpp -o datetime
// 
#if defined(__DATETIME_CPP_MAIN__)
int main()
{
	const int buffsize = 200, width = 30;
	char buff[buffsize];
	
# if defined(__DATETIME_FORMAT_ASCTIME__)
	const char *str = "Fri Dec  2 12:34:56 2011";
	DateTime::Format format = DateTime::AscTime;
# endif
# if defined(__DATETIME_FORMAT_EUROPEAN__)
	const char *str = "2011-12-02 12:34:56";
	DateTime::Format format = DateTime::European;
# endif

	DateTime::SetFormat(format);

	// 
	// Display list of format strings:
	// 
	DateTime datetime(str);
	std::cout << std::setw(width) << std::left << "Format:" << "Datetime:" << std::endl;
	std::cout << std::setw(width) << std::left << "-------" << "---------" << std::endl;
	for(const char **fmt = DateTime::Formats; *fmt; ++fmt) {
		if(strftime(buff, sizeof(buff), *fmt, &datetime.GetDateTime())) {
			std::cout << std::setw(width) << *fmt << buff << std::endl;
		}
	}
	std::cout << std::endl;
	
	// 
	// Test constructors and other functions:
	// 
	{
		std::cout << "Initialization:\n";
		std::cout << "---------------\n";
		std::cout << std::setw(width) << DateTime() << "DateTime()" << std::endl;
		std::cout << std::setw(width) << DateTime(time(0)) << "DateTime(time(0))" << std::endl;
		std::cout << std::setw(width) << DateTime(2011, 12, 02, 12, 34, 56) << "DateTime(2011, 12, 02, 12, 34, 56)" << std::endl;	
		std::cout << std::setw(width) << DateTime(str) << "DateTime(\"" << str << "\")" << std::endl;
		std::cout << std::setw(width) << DateTime(std::string(str)) << "DateTime(std::string(\"" << str << "\"))" << std::endl;
	
		// Should throw (input/format mismatch):
		try {
			std::cout << std::setw(width) << DateTime(str, DateTime::Date_RFC8222) << "DateTime(str, DateTime::Date_RFC8222)" << std::endl;
		} catch(DateTime::Exception) {
			// ignore
		}
		
		std::cout << std::setw(width) << DateTime(str, format) << "DateTime(str, " << format << ")" << std::endl;
		const char *fmt = DateTime::Formats[format];
		std::cout << std::setw(width) << DateTime(str, fmt) << "DateTime(str, " << fmt << ")" << std::endl;
		
# if defined(__DATETIME_MUTABLE__)
		datetime.Read(str);
		std::cout << std::setw(width) << datetime << "DateTime::Read(\"" << str << "\")" << std::endl;
		datetime.Read(std::string(str));
		std::cout << std::setw(width) << datetime << "DateTime::Read(std::string(\"" << str << "\"))" << std::endl;
# endif
		
		std::cout << std::setw(width) << datetime.operator std::time_t() << "DateTime::operator std::time_t()" << std::endl;
		
		std::cout << std::setw(width) << DateTime::Now() << "DateTime::Now()" << std::endl;
		std::cout << std::setw(width) << DateTime::Min() << "DateTime::Min()" << std::endl;
		std::cout << std::setw(width) << DateTime::Max() << "DateTime::Max()" << std::endl;
		std::cout << std::setw(width) << DateTime::Epoch() << "DateTime::Epoch()" << std::endl;
#if defined(__x86_64__)		
		std::cout << std::setw(width) << DateTime::I386() << "DateTime::I386()" << std::endl;
#endif
		std::cout << std::setw(width) << DateTime::GetFormat() << "DateTime::GetFormat()" << std::endl;	
		std::cout << std::endl;
	}
	
	// 
	// Test reading date/time from input:
	//
	{
		/*
		 std::cout << "Input date (" << DateTime::GetFormat() << "): ";
		 std::cin >> datetime;
		 std::cout << std::setw(width) << datetime << std::endl;
		 std::cout << std::endl;
		 */
	}
	
	// 
	// Test arithmetric and comparision operators:
	// 
	{
		DateTime dt1 = DateTime::Now();
		DateTime dt2 = dt1;
		DateTime dt3(1, 0, 0);
	
		std::cout << "Operators:\n";
		std::cout << "----------\n";
		std::cout << std::setw(width) << dt1 << "DateTime(dt1)" << std::endl;
		std::cout << std::setw(width) << dt2 << "DateTime(dt2)" << std::endl;
		std::cout << std::setw(width) << dt3 << "DateTime(dt3)" << std::endl;
		std::cout << std::endl;
		
# if defined(__DATETIME_MUTABLE__)
		std::cout << std::setw(width) << dt1 + dt3 << "dt1 + dt3" << std::endl;
		std::cout << std::setw(width) << dt1 - dt3 << "dt1 - dt3" << std::endl;
		std::cout << std::setw(width) << dt3++ << "dt3++" << std::endl;
		std::cout << std::setw(width) << ++dt3 << "++dt3" << std::endl;
		std::cout << std::setw(width) << dt3-- << "dt3--" << std::endl;
		std::cout << std::setw(width) << --dt3 << "--dt3" << std::endl;
		dt1 = dt2;
		std::cout << std::setw(width) << (dt1 += dt3) << "dt1 += dt3" << std::endl;
		dt1 = dt2;
		std::cout << std::setw(width) << (dt1 -= dt3) << "dt1 -= dt3" << std::endl;
		dt1 = dt2;
		std::cout << std::setw(width) << (dt1 += 3600) << "dt1 += 3600" << std::endl;
		dt1 = dt2;
		std::cout << std::setw(width) << (dt1 -= 3600) << "dt1 -= 3600" << std::endl;
# endif				
		dt1 = dt2;
		std::cout << std::setw(width) << std::boolalpha << (dt1 == dt3) << "dt1 == dt3" << std::endl;
		std::cout << std::setw(width) << std::boolalpha << (dt1 == dt2) << "dt1 == dt2" << std::endl;
		std::cout << std::setw(width) << std::boolalpha << (dt1 != dt3) << "dt1 != dt3" << std::endl;
		std::cout << std::setw(width) << std::boolalpha << (dt1 != dt2) << "dt1 != dt2" << std::endl;
		std::cout << std::setw(width) << std::boolalpha << (dt1 <= dt2) << "dt1 <= dt2" << std::endl;
		std::cout << std::setw(width) << std::boolalpha << (dt1 <= dt3) << "dt1 <= dt3" << std::endl;
		std::cout << std::setw(width) << std::boolalpha << (dt2 >= dt1) << "dt2 >= dt1" << std::endl;
		std::cout << std::setw(width) << std::boolalpha << (dt3 >= dt1) << "dt3 >= dt1" << std::endl;
		std::cout << std::setw(width) << std::boolalpha << (dt2 <  dt1) << "dt2 <  dt1" << std::endl;
		std::cout << std::setw(width) << std::boolalpha << (dt3 <  dt1) << "dt3 <  dt1" << std::endl;
		std::cout << std::setw(width) << std::boolalpha << (dt1 >  dt3) << "dt1 >  dt3" << std::endl;
		std::cout << std::setw(width) << std::boolalpha << (dt1 >  dt2) << "dt1 >  dt2" << std::endl;
		std::cout << std::endl;
	}

	// 
	// Demonstrate property get/set methods, including add/next:
	// 
	{
# if defined(__DATETIME_PROPGET__) || defined(__DATETIME_PROPSET__)
		std::cout << "Properties:\n";
		std::cout << "-----------\n";
		DateTime dt1 = DateTime::Now();
		DateTime dt2(2005, 12, 31, 12, 34, 56);
		DateTime dt3;
# endif
# if defined(__DATETIME_PROPGET__)
		std::cout << dt1 << ":" << std::endl;
		std::cout << std::setw(width) << dt1.GetYear() << "DateTime::GetYear()" << std::endl;
		std::cout << std::setw(width) << dt1.GetMonth() << "DateTime::GetMonth()" << std::endl;
		std::cout << std::setw(width) << dt1.GetDay() << "DateTime::GetDay()" << std::endl;
		std::cout << std::setw(width) << dt1.GetHour() << "DateTime::GetHour()" << std::endl;
		std::cout << std::setw(width) << dt1.GetMinute() << "DateTime::GetMinute()" << std::endl;
		std::cout << std::setw(width) << dt1.GetSecond() << "DateTime::GetSecond()" << std::endl;
		std::cout << std::setw(width) << dt1.GetWeekDay() << "DateTime::GetWeekDay()" << std::endl;
		std::cout << std::setw(width) << dt1.GetYearDay() << "DateTime::GetYearDay()" << std::endl;
		std::cout << std::setw(width) << dt1.GetIsDST() << "DateTime::GetIsDST()" << std::endl;
		std::cout << std::endl;
# endif
# if defined(__DATETIME_PROPSET__)
		std::cout << dt2 << ":" << std::endl;
		dt1.SetYear(dt2.GetYear());
		std::cout << std::setw(width) << dt1.GetYear() << "DateTime::SetYear(" << dt2.GetYear() << ")" << std::endl;
		dt1.SetMonth(dt2.GetMonth());
		std::cout << std::setw(width) << dt1.GetMonth() << "DateTime::SetMonth(" << dt2.GetMonth() << ")" << std::endl;
		dt1.SetDay(dt2.GetDay());
		std::cout << std::setw(width) << dt1.GetDay() << "DateTime::SetDay(" << dt2.GetDay() << ")" << std::endl;
		dt1.SetHour(dt2.GetHour());
		std::cout << std::setw(width) << dt1.GetHour() << "DateTime::SetHour(" << dt2.GetHour() << ")" << std::endl;
		dt1.SetMinute(dt2.GetMinute());
		std::cout << std::setw(width) << dt1.GetMinute() << "DateTime::SetMinute(" << dt2.GetMinute() << ")" << std::endl;
		dt1.SetSecond(dt2.GetSecond());
		std::cout << std::setw(width) << dt1.GetSecond() << "DateTime::SetSecond(" << dt2.GetSecond() << ")" << std::endl;
		
		dt1.SetDate(dt2.GetYear(), dt2.GetMonth(), dt2.GetDay());
		std::cout << std::setw(width) << dt1.Write(DateTime::GetFormat(DateTime::Date_ISO8601)) << "DateTime::SetDate(" << dt2.GetYear() << ", " << dt2.GetMonth() << ", " << dt2.GetDay() << ")" << std::endl;
		dt1.SetTime(dt2.GetHour(), dt2.GetMinute(), dt2.GetSecond());
		std::cout << std::setw(width) << dt1.Write(DateTime::GetFormat(DateTime::Time_ISO8601)) << "DateTime::SetTime(" << dt2.GetHour() << ", " << dt2.GetMinute() << ", " << dt2.GetSecond() << ")" << std::endl;
		std::cout << std::endl;
# endif
# if defined(__DATETIME_PROPGET__)
		std::cout << dt2 << ":" << std::endl;
		std::cout << std::setw(width) << dt2.NextYear() << "DateTime::NextYear(" << dt2 << ")" << std::endl;
		std::cout << std::setw(width) << dt2.NextMonth() << "DateTime::NextMonth(" << dt2 << ")" << std::endl;
		std::cout << std::setw(width) << dt2.NextDay() << "DateTime::NextDay(" << dt2 << ")" << std::endl;
		std::cout << std::setw(width) << dt2.NextHour() << "DateTime::NextHour(" << dt2 << ")" << std::endl;
		std::cout << std::setw(width) << dt2.NextMinute() << "DateTime::NextMinute(" << dt2 << ")" << std::endl;
		std::cout << std::setw(width) << dt2.NextSecond() << "DateTime::NextSecond(" << dt2 << ")" << std::endl;
		std::cout << std::setw(width) << dt2.NextWeek().Normalize() << "DateTime::NextWeek(" << dt2 << ")" << std::endl;
		std::cout << std::endl;
# endif
# if defined(__DATETIME_PROPSET__)
		dt1 = DateTime(2000, 1, 1);
		dt2 = DateTime(2, 3, 4, 5, 6, 7);
		dt3 = dt1;
		std::cout << dt1 << ":" << std::endl;
		dt1.AddYear(dt2.GetYear() - DateTime::YEAR_SHIFT);
		std::cout << std::setw(width) << dt1.Normalize().Write() << "DateTime::AddYear(" << dt2.GetYear() - DateTime::YEAR_SHIFT << ")" << std::endl;
		dt1 = dt3;
		dt1.AddMonth(dt2.GetMonth());
		std::cout << std::setw(width) << dt1.Normalize().Write() << "DateTime::AddMonth(" << dt2.GetMonth() << ")" << std::endl;
		dt1 = dt3;
		dt1.AddDay(dt2.GetDay());
		std::cout << std::setw(width) << dt1.Normalize().Write() << "DateTime::AddDay(" << dt2.GetDay() << ")" << std::endl;
		dt1 = dt3;
		dt1.AddHour(dt2.GetHour());
		std::cout << std::setw(width) << dt1.Normalize().Write() << "DateTime::AddHour(" << dt2.GetHour() << ")" << std::endl;
		dt1 = dt3;
		dt1.AddMinute(dt2.GetMinute());
		std::cout << std::setw(width) << dt1.Normalize().Write() << "DateTime::AddMinute(" << dt2.GetMinute() << ")" << std::endl;
		dt1 = dt3;
		dt1.AddSecond(dt2.GetSecond());
		std::cout << std::setw(width) << dt1.Normalize().Write() << "DateTime::AddSecond(" << dt2.GetSecond() << ")" << std::endl;
		dt1 = dt3;
		dt1.AddWeek(8);
		std::cout << std::setw(width) << dt1.Normalize().Write() << "DateTime::AddWeek(8)" << std::endl;
# endif
	}
}

#endif // __DATETIME_CPP_MAIN__
