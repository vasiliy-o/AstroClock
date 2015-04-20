#include <array>
#include "datetime.h"
#include "types.h"

namespace Astro {

	// must match enum class body
	array<swe_body, bodies_N>  swe_bodies{ {
		swe_body::se_sun,
		swe_body::se_earth,
		swe_body::se_moon,
		swe_body::se_nnode,
		swe_body::se_snode,
		swe_body::se_mercury,
		swe_body::se_venus,
		swe_body::se_mars,
		swe_body::se_jupiter,
		swe_body::se_saturn,
		swe_body::se_uranus,
		swe_body::se_neptune,
		swe_body::se_pluto
	} };

	array<swe_calendar, calendars_N> swe_calendars{ {
		swe_calendar::se_julian,
		swe_calendar::se_gregorian
	} };

	array<swe_calendar_c, calendars_N> swe_calendars_c{ {
		swe_calendar_c::se_julian_c,
		swe_calendar_c::se_gregorian_c,
	} };
}