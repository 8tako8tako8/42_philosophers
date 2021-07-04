#include "philo.h"

static int		does_satisfy_count_eat(t_info *info, t_philo *philo)
{
	return philo->count_eat == info->num_of_each_eating;
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		usleep(200);
	while (!philo->flag_fin && !philo->flag_eat_fin && !g_flag_fin)
	{
		// printf("1: id=%d\n", philo->id);
		if (philo->id == 1)
			write(1, "#1\n", 3);
		else
			write(1, "$1\n", 3);
		take_forks(philo);
		// printf("2: id=%d\n", philo->id);
		if (philo->id == 1)
			write(1, "#2\n", 3);
		else
			write(1, "$2\n", 3);
		if (eat_spaghetti(philo->info, philo) == ERROR)
		{
			print_error_message(GETTIMEOFDAY_FAILED);
			break ;
		}
		if (philo->info->num_of_each_eating && does_satisfy_count_eat(philo->info, philo))
			philo->flag_eat_fin = TRUE;
		drop_forks(philo);
		// printf("3: id=%d\n", philo->id);
		if (philo->id == 1)
			write(1, "#3\n", 3);
		else
			write(1, "$3\n", 3);
		if (spend_sleeping(philo->info, philo) == ERROR)
		{
			print_error_message(GETTIMEOFDAY_FAILED);
			break ;
		}
		// printf("4: id=%d\n", philo->id);
		if (philo->id == 1)
			write(1, "#4\n", 3);
		else
			write(1, "$4\n", 3);
		think_deeply(philo);
		printf("id: %d, flag_fin: %d, flag_eat_fin: %d\n", philo->id, philo->flag_fin, philo->flag_eat_fin);
	}
	write(1, "5: thread finish\n", 17);
	return (NULL);
}
