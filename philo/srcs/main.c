#include "philo.h"

pthread_mutex_t	*g_fork;
pthread_mutex_t	g_fin;
pthread_mutex_t	g_eat;
pthread_mutex_t	g_print;
pthread_mutex_t	g_first_last;
int				g_flag_fin;

static void	clean_mutex(t_info *info)
{
	int	i;

	i = 0;
	while (i < (info->num_of_philos))
	{
		pthread_mutex_destroy(&g_fork[i]);
		i++;
	}
	pthread_mutex_destroy(&g_fin);
	pthread_mutex_destroy(&g_eat);
	pthread_mutex_destroy(&g_print);
	pthread_mutex_destroy(&g_first_last);
}

static void	free_memory(t_philo *philos)
{
	if (g_fork)
		free(g_fork);
	if (philos)
		free(philos);
}

int	main(int argc, char **argv)
{
	t_info	info;
	t_philo	*philos;

	if (check_arguments(argc, argv) == ERROR)
		return (print_error_message(INVALID_ARGUMENT));
	if (init_info(&info, argc, argv) == ERROR)
		return (print_error_message(TOO_MANY_PHILO));
	if (init_global_variables(&info) == ERROR)
		return (print_error_message(MALLOC_FAILED));
	philos = init_philo(&info);
	if (!philos)
	{
		free(g_fork);
		return (STATUS_ERROR);
	}
	if (init_time_start(&info, philos) == ERROR
		|| create_threads(&info, philos) == ERROR)
	{
		free_memory(philos);
		return (STATUS_ERROR);
	}
	join_threads(&info, philos);
	clean_mutex(&info);
	free_memory(philos);
	return (0);
}
