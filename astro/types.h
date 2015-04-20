#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#ifndef __GNUC__
#include "..\swlib32\swephexp.h"
#else
#include "..\swlib32\unix\src\swephexp.h"
#endif

namespace Astro {

	enum class body : int {
		sun,
		earth,
		moon,
		nnode,
		snode,
		mercury,
		venus,
		mars,
		jupiter,
		saturn,
		uranus,
		neptune,
		pluto,
		N,
		null_body
	};
	
	enum class swe_body : int {
		se_sun = SE_SUN,
		se_earth = SE_SUN,
		se_moon = SE_MOON,
		se_nnode = SE_TRUE_NODE,
		se_snode = SE_TRUE_NODE,
		se_mercury = SE_MERCURY,
		se_venus = SE_VENUS,
		se_mars = SE_MARS,
		se_jupiter = SE_JUPITER,
		se_saturn = SE_SATURN,
		se_uranus = SE_URANUS,
		se_neptune = SE_NEPTUNE,
		se_pluto = SE_PLUTO,		
	};

	enum class calendar { julian, gregorian, N };

	const int bodies_N = static_cast<int>(body::N);	
	const int calendars_N = static_cast<int>(calendar::N);

	enum class swe_calendar : int { se_julian = SE_JUL_CAL, se_gregorian = SE_GREG_CAL };
	enum class swe_calendar_c : char { se_julian_c = 'j', se_gregorian_c = 'g' };
}

#endif // TYPES_H_INCLUDED