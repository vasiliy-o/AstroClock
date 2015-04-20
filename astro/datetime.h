#ifndef DATETIME_H_INCLUDED
#define DATETIME_H_INCLUDED

#include <iostream>
#include "types.h"

namespace Astro {

	class Date {

	public:

		Date(int year, int month, int day, calendar c = calendar::gregorian);
		Date() : y{ -1 }, m{ -1 }, d{ -1 }, cal { calendar::gregorian } {}
				
		inline int year() const { return y; }
		inline int month() const { return m; }
		inline int day() const { return d; }
		
		void setYear(int year) { y = year; }
		void setMonth(int month) { m = month; }
		void setDay(int day) { d = day; }

		inline calendar calendarType() const { return cal; }

	private:

		int y, m, d;
		calendar cal;		
	};

	class Time {

	public:

		Time(int h = 12, int m = 0, int s = 0);

		inline int hours() const { return h; }
		inline int minutes() const { return m; }
		inline int seconds() const { return s; }
		inline double count() const { return c; }

		void setHour(int hours);
		void setMinute(int minutes);
		void setSecond(int seconds);

	private:
		
		int h, m, s;
		double c;

		void updateCount();
	};

	class DateTime {

	public:
		DateTime(const Date& date, const Time& time);
		DateTime() {}

		inline Date date() const { return d; }
		inline Time time() const { return t; }
		inline double julian_day() const { return jd; }

	private:
		Date d;
		Time t;
		double jd;
		
		void update_jd();
	};
	
	using namespace std;

	ostream& operator<<(ostream& os, const Time& t);
	ostream& operator<<(ostream& os, const Date& d);
	ostream& operator<<(ostream& os, const DateTime& dt);

} // namespace

#endif // DATETIME_H_INCLUDED