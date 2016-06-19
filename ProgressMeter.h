#ifndef ProgressMeter_h_
#define ProgressMeter_h_
#include <string>

class ProgressMeter
{
	public:
		// \brief Constructor creates ProgressMeter with a user defined max count and banner.
			//! Constructor creates a ProgressMeter.  max_count and banner are set to what
			//! the user requests, and percent and count are set to 0.  It also sets
			//! the clock start to the current time and prints the default message.
		ProgressMeter( int max_counts, std::string banner );

		//! Prints the total time used.
		~ProgressMeter();

		// \brief Notifies the ProgressMeter that a step has been completed.
			//! Increments count.  If the percentage, rounded to the ones place
			//! has incremented, the program calcultates new used, left, and total
			//! times, and prints the to stdout.
		void update();

	private:
		//! The count of how many times update() has been called.
		int count;

		//! The number of calls to update() to expect, defined by user.
		int max_counts;

		//! The ratio of count to maxcount, in percentage form.
		int percent;

		//! The clock that measures the time when the program started.
		clock_t start;

		//! The user defined banner which is displayed before the time statistics.
		std::string banner;

		//! Returns formatted timestamp.
		std::string printTime(int days, int hours, int minutes, int seconds);

		// \brief Converts seconds into fields for a timestamp.
			//! Uses repeated subtraction and incrementing to distribute the seconds
			//! into the days, hours, and minutes, which gives us a timestamp.
		void distributeSeconds(int *days, int *hours, int *minutes, int *seconds);
};

#endif