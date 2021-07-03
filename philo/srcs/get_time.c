#include "philo.h"

long	get_time_in_ms(void)
{
	struct timeval	tv;
	time_t			time_ms;

	if (gettimeofday(&tv, NULL) < 0)
		return (ERROR);
	time_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time_ms);
}
