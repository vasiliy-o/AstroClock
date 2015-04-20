#include <list>
#include <algorithm>
#include "swe_wrapper.h"

using namespace std;

namespace Astro {

	namespace Ephemeris {

		SweWrapper::SweWrapper(const std::string& path)
		{
			swe_set_ephe_path((char *)path.c_str());
		}

		SweWrapper::~SweWrapper()
		{
			swe_close();
		}

		double SweWrapper::body_pos(body b, double julian_day)
		{
			/*
			 target address for 6 position values: longitude, latitude, distance, long. speed, lat. speed, dist. speed
			*/
			static double coords[6];

			static char swe_error_msg[AS_MAXCH];
			static long calc_flag = 0;

			int swe_body = static_cast<int>(body_to_swe_body(b));
						
			long swe_result = swe_calc_ut(julian_day, swe_body, calc_flag, coords, swe_error_msg);

			if(calc_flag != swe_result) {

				throw runtime_error{ (string("Swiss ephemeris error: '") + swe_error_msg + "'\n").c_str() };
			}

			if(b == body::earth || b == body::snode) {

				coords[0] += 180.;
				if(coords[0] > 360.) coords[0] -= 360.;
			}

			// return ecliptic longitude of the body (in degrees [0..365), counting from the vernal equinox of the date as 0 degrees)
			return coords[0];
		}

	} // namespace

} // namespace