#include "ProgressMeter.h"
#include <iostream>
#include <string>
#include <time.h>
#include <iomanip>
#include <cstdio>
#include <sstream>

#define SECONDS_IN_DAY 86400
#define SECONDS_IN_HOUR 3600
#define SECONDS_IN_MINUTE 60

ProgressMeter::ProgressMeter( int m, std::string b ){
	count = 0;
	max_counts = m;
	percent = 0;

	banner = b;

	// Tracing:    0%     Used: 00:00:00:00   Left:  00:00:00:00    Total: 00:00:00:00
	std::cout << "\r" << banner << ": " <<
			"\t" << std::right << percent << '%' << 
			"\tUsed: " << printTime(0, 0, 0, 0) <<
			"\tLeft: " << printTime(0, 0, 0, 0) <<
			"\tTotal: " << printTime(0, 0, 0, 0);
			fflush(stdout);

	start = clock();
}

void ProgressMeter::update(){
	count++;
	if(((float)count / (float)max_counts)*100 >= (percent + 1)){
		percent++;
		clock_t current = clock() - start;

		int used_days = 0, used_hours = 0, used_minutes = 0,
			used_seconds = ((float) current) / CLOCKS_PER_SEC;

		int total_days = 0, total_hours = 0, total_minutes = 0,
			total_seconds = (((float) current) / CLOCKS_PER_SEC) * (1.0 / ((float)count / (float)max_counts));

		int left_days = 0, left_hours = 0, left_minutes = 0,
			left_seconds = total_seconds - used_seconds;

		distributeSeconds(&used_days, &used_hours, &used_minutes, &used_seconds);
		distributeSeconds(&total_days, &total_hours, &total_minutes, &total_seconds);
		distributeSeconds(&left_days, &left_hours, &left_minutes, &left_seconds);

		// banner:    24%     Used: 00:00:00:01   Left:  00:00:00:03    Total: 00:00:00:04
		std::cout << "\r" << banner << ": " <<
			"\t" << std::right << percent << '%' << 
			"\tUsed: " << printTime(used_days, used_hours, used_minutes, used_seconds) <<
			"\tLeft: " << printTime(left_days, left_hours, left_minutes, left_seconds) <<
			"\tTotal: " << printTime(total_days, total_hours, total_minutes, total_seconds);
		fflush(stdout);
	}
}

void ProgressMeter::distributeSeconds(int *days, int *hours, int *minutes, int *seconds){
	while(*seconds > SECONDS_IN_DAY){
		(*days)++;
		*seconds -= SECONDS_IN_DAY;
	}
	while(*seconds > SECONDS_IN_HOUR){
		(*hours)++;
		*seconds -= SECONDS_IN_HOUR;
	}
	while(*seconds > SECONDS_IN_MINUTE){
		(*minutes)++;
		*seconds -= SECONDS_IN_MINUTE;
	}
}

std::string ProgressMeter::printTime(int days, int hours, int minutes, int seconds){
	std::stringstream buffer;
	buffer << std::setfill ('0') << std::setw(2) << days << ":" << std::setfill ('0') << std::setw(2) << hours << ":" << std::setfill ('0') << std::setw(2) << minutes << ":" << std::setfill ('0') << std::setw(2) << seconds;
	return buffer.str();
}

ProgressMeter::~ProgressMeter(){
	clock_t current = clock() - start;

	int used_days = 0;
	int used_hours = 0;
	int used_minutes = 0;
	int used_seconds = ((float) current) / CLOCKS_PER_SEC;
	distributeSeconds(&used_days, &used_hours, &used_minutes, &used_seconds);

	// Clears stdout of old text
	std::cout << "\r                                                                                          ";

	// Banner:	Total time: 00:00:00:04
	std::cout << "\r" << banner << ": " <<
			"\tTotal time: " << printTime(used_days, used_hours, used_minutes, used_seconds) <<
			std::endl;
};