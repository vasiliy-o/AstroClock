#include <iostream>
#include "astro.h"
#include "swe_wrapper.h"

namespace Astro {

	namespace Ephemeris {

		SwissEphemeris::SwissEphemeris(const std::string& swe_path)
		{
			swe = new SweWrapper(swe_path);			
		}

		SwissEphemeris::~SwissEphemeris()
		{
			delete swe;
		}	

	} // namespace	

} // namespace