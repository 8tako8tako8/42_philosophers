#include "philo.h"

int	spend_sleeping(t_info *info, t_philo *philo)
{
	long	time_now;
	long	tmp;

	if (print_status_and_check_fin(philo, SLEEP) == ERROR)
		return (ERROR);
	tmp = get_time_in_ms();
	if (tmp == ERROR)
		return (ERROR);
	while (1)
	{
		time_now = get_time_in_ms();
		if (time_now == ERROR)
			return (ERROR);
		if ((time_now - tmp) >= info->time_to_sleep)
			break ;
		usleep(50);
	}
	return (SUCCESS);
}

int	think_deeply(t_philo *philo)
{
	if (print_status_and_check_fin(philo, THINK) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
