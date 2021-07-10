#include "philo.h"

int	init_info(t_info *info, int argc, char **argv)
{
	info->num_of_philos = ft_atoi(argv[1]);
	if (info->num_of_philos > 200)
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
	pthread_mutex_init(&g_eat, NULL);
	pthread_mutex_init(&g_print, NULL);
	g_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* (info->num_of_philos));
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

static int	init_philo_contents(int i, t_info *info, t_philo *philos)
{
	long long	time_start;

	time_start = get_time_in_ms();
	if (time_start == ERROR)
		return (ERROR);
	philos[i].id = i + 1;
	philos[i].count_eat = 0;
	philos[i].time_last_eat = time_start;
	philos[i].right_fork = i;
	if (i == info->num_of_philos - 1)
		philos[i].left_fork = 0;
	else
		philos[i].left_fork = i + 1;
	pthread_mutex_init(&(philos[i].die), NULL);
	philos[i].info = info;
	return (SUCCESS);
}

t_philo	*init_philo(t_info *info)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)malloc(sizeof(t_philo) * (info->num_of_philos));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < (info->num_of_philos))
	{
		if (init_philo_contents(i, info, philos) == ERROR)
			return (NULL);
		i++;
	}
	return (philos);
}
