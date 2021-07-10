#include "philo.h"

static int	philo_action(t_philo *philo)
{
	int	tmp;

	tmp = take_forks_and_check_fin(philo);
	if (tmp == FINISH)
		return (FINISH);
	else if (tmp == ERROR)
		return (print_error_message(GETTIMEOFDAY_FAILED));
	if (eat_spaghetti(philo->info, philo) == ERROR)
		return (print_error_message(GETTIMEOFDAY_FAILED));
	drop_forks(philo);
	if (spend_sleeping(philo->info, philo) == ERROR)
		return (print_error_message(GETTIMEOFDAY_FAILED));
	if (think_deeply(philo) == ERROR)
		return (print_error_message(GETTIMEOFDAY_FAILED));
	return (CONTINUE);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;
	int		action;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		usleep(200);
	while (!g_flag_fin)
	{
		action = philo_action(philo);
		if (action == STATUS_ERROR || action == FINISH)
			break ;
	}
	return (NULL);
}
