#include "philo.h"

static int	philo_action(t_philo *philo)
{
	int	tmp;

	tmp = take_forks_and_check_fin(philo->info, philo);
	if (tmp == ERROR)
		return (print_error_message(GETTIMEOFDAY_FAILED));
	else if (tmp == FORK_ERROR)
		return (print_error_message(NOT_TAKE_FORK));
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
	if (philo->id % 2 == 0)
		usleep(200);
	if (philo->info->num_of_philos % 2 == 1
		&& philo->id == philo->info->num_of_philos)
		usleep(200);
	while (1)
	{
		action = philo_action(philo);
		if (action == STATUS_ERROR || action == FINISH)
			break ;
		pthread_mutex_lock(&g_fin);
		if (g_flag_fin)
		{
			pthread_mutex_unlock(&g_fin);
			break ;
		}
		pthread_mutex_unlock(&g_fin);
	}
	return (NULL);
}
