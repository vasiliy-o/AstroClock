#include "datetime.h"
#include "ephemeris.h"
#include "utilities.h"
#include "swe_wrapper.h"

namespace Astro {
	
	namespace Ephemeris {

		Ephemeris::SwissEphemeris *ephemeris;
	}

	namespace Utilities {

		double to_julian_day(const Date& d, const Time& t)
		{
			int swe_calendar = static_cast<int>(calendar_to_swe_calendar(d.calendarType()));

			return swe_julday(d.year(), d.month(), d.day(), t.count(), swe_calendar);
		}

		double to_julian_day(const Date& d, const Time& t, bool *ok)
		{
			double jd;

			char swe_calendar_c = static_cast<char>(calendar_to_swe_calendar_c(d.calendarType()));

			int r = swe_date_conversion(d.year(), d.month(), d.day(), t.count(), swe_calendar_c, &jd);

			if(ok) *ok = (r == OK) ? true : false;

			return jd;
		}

		double to_julian_day(const DateTime& dt, bool *ok)
		{
			return to_julian_day(dt.date(), dt.time(), ok);
		}

		DateTime from_julian_day(double jd)
		{
			int year, month, day, hour, min;
			double sec;

			swe_jdut1_to_utc(jd, 1, &year, &month, &day, &hour, &min, &sec);

			Date d(year, month, day);
			Time t(hour, min, int(sec));

			return DateTime(d, t);
		}

		string body_name(body b)
		{
			static char name[AS_MAXCH];

			int swe_body = static_cast<int>(body_to_swe_body(b));

			return swe_get_planet_name(swe_body, name);
		}

	} // namespace

} // namespace