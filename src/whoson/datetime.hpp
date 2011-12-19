#ifndef __DATETIME_HPP__
#define __DATETIME_HPP__

#include <string>
#include <ctime>

// 
// The main scope of the DateTime class was to develop an class suitable for
// conversion of input string or stream to a standard representation of date/
// time information. The representation is done using an internal std::tm 
// struct.
// 
// Immutable:
// --------------
// The datetime class is immutable by default. Use __DATETIME_MUTABLE__ to enable 
// the mutators (SetXXX() and Read()). The property functions (SetXXX() and GetXXX()) 
// can be enabled by the __DATETIME_PROPSET__ and __DATETIME_PROPGET__ macros.
// 
// Normalizing:
// --------------
// All SetXXX() is unchecked. The Normalize() function could be utilized to normalize 
// the internal date/time representation. It was a design decision made to defere the
// normalization (a possibly costly operation) until all object modifications has been
// done, at the risk of possibly inconsistent date/time representations.
// 
// Arihmetric types and operations:
// ---------------------------------
// A fairly full set of operators is overloaded to provide datetime calculations. 
// Some considerations has to be done, i.e. simply adding two dates won't create the
// desired result. Instead to add five years to an existing date, do this:
// 
//   (a) DateTime res = datetime + DateTime(5, 0, 0);  // Use constructor DateTime(int, ...)
// 
//   (b) DateTime res = datetime;
//       res.AddYear(5);                               // Use mutator
//       res.Normalize();
// 
// Please notice that we use DateTime(5, 0, 0) in (a) as DateTime(5) sets month 
// and day to 1 by default arguments.
// 
// Notes:
// --------------
// 
// (1): Calling any one of these constructors or member functions will match the 
//      input string against all possible format strings (see DateTime::Formats). 
//      Throws an exception if no match was found.
// 
//      

#if defined(__DATETIME_EXPORT__)
# ifndef  __DATETIME_MUTABLE__
#  define __DATETIME_MUTABLE__
# endif
#endif
#if defined(__DATETIME_MUTABLE__)
# ifndef  __DATETIME_PROPGET__
#  define __DATETIME_PROPGET__
# endif
# ifndef  __DATETIME_PROPSET__
#  define __DATETIME_PROPSET__
# endif
#endif
#if defined(__DATETIME_PROPSET__)
# ifndef  __DATETIME_PROPGET__
#  define __DATETIME_PROPGET__
# endif
#endif

class DateTime
{
public:
	static const int YEAR_SHIFT  = 1900;
	static const int MONTH_SHIFT = 1;
	static const int DAY_SHIFT   = 1;
	static const int WEEK_LENGTH = 3600 * 24 * 7;
	
	enum Format {
		Locale,          // Use current locale specific format.
		Date_Locale,     // Use current locale specific format (date only).
		Time_Locale,     // Use current locale specific format (time only).
		Date_ISO8601,    // %Y-%m-%d -> yyyy-mm-dd (ISO 8601 date format).
		Time_ISO8601,    // %H:%M:%S -> hh:mm:ss   (ISO 8601 time format).
		Date_RFC8222,    // %a, %d %b %Y %T %z (RFC 2822-compliant date format).
		Date_RFC822,     // %a, %d %b %y %T %z (RFC 822-compliant date format).
		AscTime,         // Formatted as asctime(3)
	        European,        // %Y-%m-%d %H:%M:%S (Common european datetime format)
		Date_America,    // %m/%d/%y (American date representation)
		Date_Short       // %y-%m-%d -> yy-mm-dd
	};

	struct Exception {};
	
	DateTime();
	DateTime(std::time_t);
	DateTime(int year, int month = 1, int day = 1, int hour = 0, int minute = 0, int second = 0, int isdst = 0, bool normalize = true); // Might throw
	DateTime(const std::string &str);                      // Throws
	DateTime(const std::string &str, const char *fmt);     // Throws
	DateTime(const std::string &str, Format fmt);          // Throws
	DateTime(const char *str);                             // Throws (1)
	
	static const DateTime & Min() { return min; }          // Smallest DateTime
	static const DateTime & Max() { return max; }          // Largest DateTime

	static DateTime Now();                                 // Current date/time
	static DateTime Epoch();                               // UNIX epoch start
	
#if defined(__x86_64__)
	static DateTime I386();                                // Largest DateTime (32-bit)
#endif
	
	friend bool operator ==(const DateTime &, const DateTime &);
	friend bool operator !=(const DateTime &, const DateTime &);
	friend bool operator  >(const DateTime &, const DateTime &);
	friend bool operator  <(const DateTime &, const DateTime &);
	friend bool operator >=(const DateTime &, const DateTime &);
	friend bool operator <=(const DateTime &, const DateTime &);
	
	friend std::istream & operator >>(std::istream &, DateTime &);
	friend std::ostream & operator <<(std::ostream &, const DateTime &);

	DateTime & Normalize();                                // Throws
	
#if defined(__DATETIME_MUTABLE__)
	friend DateTime operator +(const DateTime &, const DateTime &);
	friend DateTime operator -(const DateTime &, const DateTime &);

	DateTime & operator ++();
	DateTime & operator --();
	
	DateTime operator ++(int);
	DateTime operator --(int);	

	DateTime & operator +=(const DateTime &);
	DateTime & operator -=(const DateTime &);
	
	DateTime & operator +=(int sec);
	DateTime & operator -=(int sec);
#endif
	
	operator std::time_t() const { return GetTimestamp(); }      // time_t t = DateTime(...);
	
	std::time_t GetTimestamp() const { tm t = d.tm; return std::mktime(&t); }
	const std::tm & GetDateTime() const { return d.tm; }
		
	static const char * GetFormat() { return fmt; }        // Get default input/output format
	static const char * GetFormat(Format f) { return Formats[f]; }
	static void SetFormat(const char *f) { fmt = f; }      // Set default input/output format
	static void SetFormat(Format f) { fmt = Formats[f]; }  // Set default input/output format
	
	static const char *Formats[];                          // List of format strings

#if defined(__DATETIME_PROPGET__)
	DateTime NextYear() const;
	DateTime NextMonth() const;
	DateTime NextDay() const;
	DateTime NextHour() const;
	DateTime NextMinute() const;
	DateTime NextSecond() const;
	DateTime NextWeek() const;
	
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
	int GetHour() const;
	int GetMinute() const;
	int GetSecond() const;
	int GetWeekDay() const;
	int GetYearDay() const;
	bool GetIsDST() const;
#endif

#if defined(__DATETIME_PROPSET__)
	void AddDate(int y, int m, int d);  // Unchecked
	void AddTime(int h, int m, int d);  // Unchecked
	void AddYear(int v);                // Unchecked
	void AddMonth(int v);               // Unchecked
	void AddDay(int v);                 // Unchecked
	void AddHour(int v);                // Unchecked
	void AddMinute(int v);              // Unchecked
	void AddSecond(int v);              // Unchecked
	void AddWeek(int v);                // Unchecked
	
	void SetDate(int y, int m, int d);  // Unchecked
	void SetTime(int h, int m, int d);  // Unchecked
	void SetYear(int v);                // Unchecked
	void SetMonth(int v);               // Unchecked
	void SetDay(int v);                 // Unchecked
	void SetHour(int v);                // Unchecked
	void SetMinute(int v);              // Unchecked
	void SetSecond(int v);              // Unchecked
	void SetWeekDay(int v);             // Unchecked
	void SetYearDay(int v);             // Unchecked
	void SetIsDST(bool v);              // Unchecked
#endif

	void Write(std::string &str) const { Write(str, fmt); }
	void Write(std::string &str, const char *fmt) const { str = Write(fmt); }
	std::string Write() const { return Write(fmt); }
	std::string Write(const char *fmt) const;
	
#if ! defined(__DATETIME_MUTABLE__)
protected:
#endif
	void Read(const char *str);                            // Set date/time from str (1)
	void Read(std::string str) { Read(str.c_str()); }
	
private:
	struct Data { std::tm tm; Data(); bool Set(const char *str, const char *fmt); } d;
	static DateTime min;
	static DateTime max;
	static const char *fmt;
};

#if defined(__DATETIME_MUTABLE__)
inline DateTime operator +(const DateTime &l, const DateTime &r)
{
	DateTime d(l);
	return d.operator+=(r);
}

inline DateTime operator -(const DateTime &l, const DateTime &r)
{
	DateTime d(l);
	return d.operator-=(r);
}

inline DateTime & DateTime::operator ++()
{
	d.tm.tm_sec++;
	return *this;
}

inline DateTime & DateTime::operator --()
{
	d.tm.tm_sec--;
	return *this;
}

inline DateTime DateTime::operator ++(int)
{
	DateTime dt(*this);
	d.tm.tm_sec++;
	return dt;
}

inline DateTime DateTime::operator --(int)
{
	DateTime dt(*this);
	d.tm.tm_sec--;
	return dt;
}

inline DateTime & DateTime::operator +=(int sec)
{
	d.tm.tm_sec += sec;
	return *this;
}

inline DateTime & DateTime::operator -=(int sec)
{
	d.tm.tm_sec -= sec;
	return *this;
}
#endif // defined(__DATETIME_MUTABLE__)

inline bool operator >=(const DateTime &l, const DateTime &r)
{
	return l > r || l == r;
}

inline bool operator <=(const DateTime &l, const DateTime &r)
{
	return l < r || l == r;
}

#if defined(__DATETIME_PROPSET__)
inline void DateTime::AddDate(int year, int month, int mday)
{
	d.tm.tm_year += year;
	d.tm.tm_mon  += month;
	d.tm.tm_mday += mday;
}

inline void DateTime::AddTime(int hour, int minute, int second)
{
	d.tm.tm_hour += hour; 
	d.tm.tm_min  += minute;
	d.tm.tm_sec  += second;
}

inline void DateTime::AddYear(int v)
{ 
	d.tm.tm_year += v; 
}

inline void DateTime::AddMonth(int v)
{ 
	d.tm.tm_mon += v; 
}

inline void DateTime::AddDay(int v)
{ 
	d.tm.tm_mday += v; 
}

inline void DateTime::AddHour(int v)
{ 
	d.tm.tm_hour += v; 
}

inline void DateTime::AddMinute(int v)
{
	d.tm.tm_min += v; 
}

inline void DateTime::AddSecond(int v)
{ 
	d.tm.tm_sec += v; 
}

inline void DateTime::AddWeek(int v)
{
	d.tm.tm_sec += v * WEEK_LENGTH;
}

inline void DateTime::SetDate(int year, int month, int mday)
{
	d.tm.tm_year = year  - YEAR_SHIFT; 
	d.tm.tm_mon  = month - MONTH_SHIFT;
	d.tm.tm_mday = mday;
}

inline void DateTime::SetTime(int hour, int minute, int second)
{
	d.tm.tm_hour = hour; 
	d.tm.tm_min  = minute;
	d.tm.tm_sec  = second;
}

inline void DateTime::SetYear(int v)
{ 
	d.tm.tm_year  = v - YEAR_SHIFT; 
}

inline void DateTime::SetMonth(int v)
{ 
	d.tm.tm_mon   = v - MONTH_SHIFT; 
}

inline void DateTime::SetDay(int v)
{
	d.tm.tm_mday  = v; 
}

inline void DateTime::SetHour(int v)
{ 
	d.tm.tm_hour  = v; 
}

inline void DateTime::SetMinute(int v)
{ 
	d.tm.tm_min   = v; 
}

inline void DateTime::SetSecond(int v)
{ 
	d.tm.tm_sec   = v; 
}

inline void DateTime::SetWeekDay(int v)
{ 
	d.tm.tm_wday  = v; 
}

inline void DateTime::SetYearDay(int v) 
{ 
	d.tm.tm_yday  = v; 
}

inline void DateTime::SetIsDST(bool v)
{ 
	d.tm.tm_isdst = v; 
}
#endif  // defined(__DATETIME_PROPSET__)

#if defined(__DATETIME_PROPGET__)
inline DateTime DateTime::NextYear() const
{ 
	DateTime dt = *this; 
	dt.d.tm.tm_year += 1; 
	return dt; 
}

inline DateTime DateTime::NextMonth() const
{ 
	DateTime dt = *this; 
	dt.d.tm.tm_mon += 1; 
	return dt; 
}

inline DateTime DateTime::NextDay() const 
{ 
	DateTime dt = *this; 
	dt.d.tm.tm_mday += 1; 
	return dt; 
}

inline DateTime DateTime::NextHour() const
{ 
	DateTime dt = *this;
	dt.d.tm.tm_hour += 1;
	return dt;
}

inline DateTime DateTime::NextMinute() const {
	DateTime dt = *this;
	dt.d.tm.tm_min += 1;
	return dt;
}

inline DateTime DateTime::NextSecond() const
{
	DateTime dt = *this;
	dt.d.tm.tm_sec += 1;
	return dt;
}

inline DateTime DateTime::NextWeek() const
{
	DateTime dt = *this;
	dt.d.tm.tm_sec += WEEK_LENGTH;
	return dt;
}

inline int DateTime::GetYear() const
{ 
	return d.tm.tm_year + YEAR_SHIFT; 
}

inline int DateTime::GetMonth() const
{ 
	return d.tm.tm_mon  + MONTH_SHIFT; 
}

inline int DateTime::GetDay() const
{ 
	return d.tm.tm_mday; 
}

inline int DateTime::GetHour() const
{ 
	return d.tm.tm_hour; 
}

inline int DateTime::GetMinute() const
{ 
	return d.tm.tm_min; 
}

inline int DateTime::GetSecond() const
{ 
	return d.tm.tm_sec; 
}

inline int DateTime::GetWeekDay() const
{ 
	return d.tm.tm_wday;
}

inline int DateTime::GetYearDay() const
{ 
	return d.tm.tm_yday;
}

inline bool DateTime::GetIsDST() const
{ 
	return d.tm.tm_isdst;
}
#endif  // defined(__DATETIME_PROPGET__)

#endif  // __DATETIME_HPP__
