#include "philo.h"

pthread_mutex_t	*g_fork;
pthread_mutex_t	g_fin;
pthread_mutex_t	g_die;
pthread_mutex_t	g_eat;
pthread_mutex_t	g_print;
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
	pthread_mutex_destroy(&g_die);
	pthread_mutex_destroy(&g_eat);
	pthread_mutex_destroy(&g_print);
}

void	free_memory(t_philo *philos)
{
	free(g_fork);
	free(philos);
}

int	main(int argc, char **argv)
{
	t_info	info;
	t_philo	*philos;

	if (check_arguments(argc, argv) == ERROR)
		return (print_error_message(INVALID_ARGUMENT));
	if (init_info(&info, argc, argv) == ERROR)
		return (print_error_message(ONLY_ONE_PHILO));
	if (init_global_variables(&info) == ERROR)
		return (print_error_message(MALLOC_FAILED));
	philos = init_philo(&info);
	if (!philos)
		return (print_error_message(MALLOC_OR_GETTIMEOFDAY_FAILED));
	if (create_threads(&info, philos) == ERROR)
		return (print_error_message(PTHREAD_CREATE_FAILED));
	join_threads(&info, philos);
	clean_mutex(&info);
	free_memory(philos);
	return (0);
}
