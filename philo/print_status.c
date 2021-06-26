#include <stdio.h>
#include <sys/time.h>

#define FORK 0
#define EAT 1
#define SLEEP 2
#define THINK 3
#define DIE 4

typedef struct s_info
{
	int			num_of_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_of_each_eating;
	long		start_time;
	int			index;
	
}				t_info;

void	print_status(t_info *info, int status)
{
	if (status == FORK)
		printf("%ld %d has taken a fork\n", info->start_time, info->index);
	else if (status == EAT)
		printf("%ld %d is eating\n", info->start_time, info->index);
	else if (status == SLEEP)
		printf("%ld %d is sleeping\n", info->start_time, info->index);
	else if (status == THINK)
		printf("%ld %d is thinking\n", info->start_time, info->index);
	else if (status == DIE)
		printf("%ld %d died\n", info->start_time, info->index);
}

/* long	get_time_in_ms(void)
{
	struct timeval	tv;
	time_t			time_ms;

	if (gettimeofday(&tv, NULL) < 0)
		return (-1);
	time_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time_ms);	
} */

/* int main()
{
	t_info info;

	info.index = 1;
	info.start_time = get_time_in_ms();
	print_status(&info, FORK);
	print_status(&info, EAT);
	print_status(&info, SLEEP);
	print_status(&info, THINK);
	print_status(&info, DIE);
} */