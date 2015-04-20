#ifndef EPHEMERIS_H_INCLUDED
#define EPHEMERIS_H_INCLUDED

#include "datetime.h"
#include "swe_wrapper.h"

namespace Astro {

	namespace Ephemeris {
		
		class SwissEphemeris {

		public:

			SwissEphemeris(const std::string& swe_path);
			~SwissEphemeris();

			inline double pos(body b, const DateTime& dt) const
			{
				return swe->body_pos(b, dt.date(), dt.time());
			}

			inline double pos(body b, const Date& d, const Time& t) const
			{
				return swe->body_pos(b, d, t);
			}

			inline double pos(body b, double julian_day) const
			{
				return swe->body_pos(b, julian_day);
			}
			
		private:

			SweWrapper *swe;
		};

		extern Ephemeris::SwissEphemeris *ephemeris;

	} // namespace

} // namespace 

#endif // EPHEMERIS_H_INCLUDED