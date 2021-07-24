#include "philo.h"

int	create_threads(t_info *info, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < (info->num_of_philos))
	{
		if (pthread_create(&(philos[i].thread), NULL,
				&philo_life, (void *)&(philos[i])) != 0)
		{
			print_error_message(PTHREAD_CREATE_FAILED);
			return (ERROR);
		}
		i++;
	}
	i = 0;
	while (i < (info->num_of_philos))
	{
		if (pthread_create(&(philos[i].watcher), NULL,
				&death_watcher, (void *)&(philos[i])) != 0)
		{
			print_error_message(PTHREAD_CREATE_FAILED);
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

void	join_threads(t_info *info, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < (info->num_of_philos))
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < (info->num_of_philos))
	{
		pthread_join(philos[i].watcher, NULL);
		i++;
	}
}
