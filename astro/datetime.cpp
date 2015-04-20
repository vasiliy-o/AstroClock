#include <chrono>
#include <sstream>
#include <ctime>
#include "datetime.h"
#include "utilities.h"

namespace Astro {

	Date::Date(int year, int month, int day, calendar c)
	:
		y(year), m(month), d(day), cal(c)
	{
	}	

	DateTime::DateTime(const Date& date, const Time& time)
	:
		d{ date }, t{ time }
	{
		update_jd();
	}

	void DateTime::update_jd()
	{
		bool ok;
		jd = Utilities::to_julian_day(*this, &ok);
		
		if(!ok) {

			ostringstream msg;
			msg << "Invalid date/time: " << *this;
			throw runtime_error{ msg.str() };
		}
	}

	Time::Time(int h, int m, int s)
	:
		h(h), m(m), s(s)
	{
		updateCount();
	}

	void Time::updateCount()
	{
		chrono::duration<double, ratio<3600>> d_hours;

		d_hours = chrono::hours{ h } + chrono::minutes{ m } + chrono::seconds{ s };

		c = d_hours.count();
	}

	void Time::setHour(int hours)
	{
		h = hours;
		updateCount();
	}

	void Time::setMinute(int minutes)
	{
		m = minutes;
		updateCount();
	}

	void Time::setSecond(int seconds)
	{
		s = seconds;
		updateCount();
	}

	ostream& operator<<(ostream& os, const Time& t) {

		return os << t.hours() << ":" << t.minutes() << ":" << t.seconds();
	}

	ostream& operator<<(ostream& os, const Date& d) {

		return os << d.year() << "." << d.month() << "." << d.day();
	}

	ostream& operator<<(ostream& os, const DateTime& dt) {

		return os << dt.date() << " " << dt.time();
	}
}