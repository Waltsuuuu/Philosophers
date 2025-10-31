#include "philosophers.h"

// Returns the current system time in milliseconds.
//
// gettimeofday() fills 'time_data' with:
// 	- (time_data.tv_sec) seconds
//  - (time_data.tv_usec) microseconds
//
// Conversion:
// 	1 second		= 1000 milliseconds
// 	1 millisecond	= 1000 microseconds
//
// Convert seconds and microseconds to milliseconds,
// then add them to get the current time in milliseconds.
long	fetch_time_ms(void)
{
	struct timeval	time_data;

	if (gettimeofday(&time_data, NULL) != SUCCESS)
		return (0);
	return (time_data.tv_sec * 1000L + time_data.tv_usec / 1000L);
}

