#include "philo.h"

pthread_mutex_t	*g_fork;
pthread_mutex_t	g_print;//いらないかも
pthread_mutex_t	g_die;
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
	// dieとprintも
	free(g_fork);
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
	write(1, "finish", 6);
	clean_mutex(&info);
	return (0);
}
