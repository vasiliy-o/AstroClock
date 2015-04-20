#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

#include <array>
#include "datetime.h"

namespace Astro {	
	
	namespace Utilities {

		DateTime from_julian_day(double jd);

		double to_julian_day(const Date& d, const Time& t);
		double to_julian_day(const Date& d, const Time& t, bool *ok);	
		double to_julian_day(const DateTime& dt, bool *ok);

		string body_name(body b);
	}
}

#endif // UTILITIES_H_INCLUDED