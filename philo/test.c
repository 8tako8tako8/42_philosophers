#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

long	get_time_in_ms(void)
{
	struct timeval	tv;
	time_t			time_ms;

	if (gettimeofday(&tv, NULL) < 0)
		return 0;
	time_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time_ms);
}

void	spend_sleeping(void)
{
	long	time_now;
	long	tmp;

	tmp = get_time_in_ms();
	printf("%ld\n", tmp);
	while (1)
	{
		time_now = get_time_in_ms();
		if ((time_now - tmp) >= 100)
			break ;
		usleep(100);
	}
	printf("%ld\n", time_now);
}

int main()
{
    spend_sleeping();
}