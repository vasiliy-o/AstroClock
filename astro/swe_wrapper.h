#ifndef SWE_WRAPPER_H_INCLUDED
#define SWE_WRAPPER_H_INCLUDED

#include <array>
#include <string>
#include "utilities.h"
#include "datetime.h"
#include "types.h"

namespace Astro {

	namespace Ephemeris {

		/*
		 wrapper for swiss ephemeris swe_calc_ut() function (swlib32.lib)
		*/
		class SweWrapper {

		public:

			SweWrapper(const std::string& path);
			~SweWrapper();

			double body_pos(body b, double julian_day);			

			inline double body_pos(body b, const Date& d, const Time& t)
			{
				double julian_day = Utilities::to_julian_day(d, t);

				return body_pos(b, julian_day);
			}
		};		
	
	} // namespace

	extern array<swe_body, bodies_N> swe_bodies;
	extern array<swe_calendar, calendars_N> swe_calendars;
	extern array<swe_calendar_c, calendars_N> swe_calendars_c;

	inline swe_body body_to_swe_body(body b)
	{		
		return swe_bodies[static_cast<int>(b)];
	}

	inline swe_calendar calendar_to_swe_calendar(calendar c)
	{
		return swe_calendars[static_cast<int>(c)];
	}

	inline swe_calendar_c calendar_to_swe_calendar_c(calendar c)
	{
		return swe_calendars_c[static_cast<int>(c)];
	}

} // namespace

#endif // SWE_WRAPPER_H_INCLUDED