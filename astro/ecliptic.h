#ifndef ECLIPTIC_H_INCLUDED
#define ECLIPTIC_H_INCLUDED

namespace Astro {

	namespace Ecliptic {

		template<int N>
		class Divider {

		public:
			Divider(double start) : start_(start) {}

			inline int pos(double abs_pos)
			{
				abs_pos -= start_;
				if(abs_pos < 0) abs_pos += 360.;

				return int(abs_pos / (360. / N));
			}

		private:
			double start_;
		};		

	} // namespace

} // namespace 

#endif // ECLIPTIC_H_INCLUDED