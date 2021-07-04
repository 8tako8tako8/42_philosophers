#include "philo.h"

int	init_info(t_info *info, int argc, char **argv)
{
	info->num_of_philos = ft_atoi(argv[1]);
	if (info->num_of_philos == 1)
		return (ERROR);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		info->num_of_each_eating = -1;
	if (argc == 6)
		info->num_of_each_eating = ft_atoi(argv[5]);
	info->count_all_eat = 0;
	return (SUCCESS);
}

int	init_global_variables(t_info *info)
{
	int		i;

	g_flag_fin = FALSE;
	pthread_mutex_init(&g_fin, NULL);
	pthread_mutex_init(&g_die, NULL);
	pthread_mutex_init(&g_eat, NULL);
	pthread_mutex_init(&g_print, NULL);
	g_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (info->num_of_philos));
	if (!g_fork)
		return (ERROR);
	i = 0;
	while (i < (info->num_of_philos))
	{
		pthread_mutex_init(&g_fork[i], NULL);
		i++;
	}
	return (SUCCESS);
}

t_philo	*init_philo(t_info *info)
{
	t_philo	*philo;
	long	time_start;
	int		i;

	philo = (t_philo *)malloc(sizeof(t_philo) * (info->num_of_philos));
	if (!philo)
		return (NULL);
	time_start = get_time_in_ms();
	if (time_start == ERROR)
		return (NULL);
	i = 0;
	while (i < (info->num_of_philos))
	{
		philo[i].id = i + 1;
		philo[i].count_eat = 0;
		philo[i].flag_eat_fin = FALSE;
		philo[i].flag_fin = FALSE;
		philo[i].time_last_eat = time_start;
		philo[i].right_fork = i;
		if (i == info->num_of_philos - 1)
			philo[i].left_fork = 0;
		else
			philo[i].left_fork = i + 1;
		philo[i].info = info;
		i++;
	}
	return (philo);
}
