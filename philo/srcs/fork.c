#include "philo.h"

static int	take_forks_in_case_first_or_last_person(t_philo *philo)
{
	pthread_mutex_lock(&g_first_last);
	pthread_mutex_lock(&g_fork[philo->left_fork]);
	if (print_status_and_check_fin(philo, FORK) == ERROR)
		return (ERROR);
	pthread_mutex_lock(&g_fork[philo->right_fork]);
	if (print_status_and_check_fin(philo, FORK) == ERROR)
		return (ERROR);
	pthread_mutex_unlock(&g_first_last);
	return (CONTINUE);
}

static int	take_forks_in_case_even_person(t_philo *philo)
{
	pthread_mutex_lock(&g_fork[philo->right_fork]);
	if (print_status_and_check_fin(philo, FORK) == ERROR)
		return (ERROR);
	pthread_mutex_lock(&g_fork[philo->left_fork]);
	if (print_status_and_check_fin(philo, FORK) == ERROR)
		return (ERROR);
	return (CONTINUE);
}

static int	take_forks_in_case_odd_person(t_philo *philo)
{
	pthread_mutex_lock(&g_fork[philo->left_fork]);
	if (print_status_and_check_fin(philo, FORK) == ERROR)
		return (ERROR);
	pthread_mutex_lock(&g_fork[philo->right_fork]);
	if (print_status_and_check_fin(philo, FORK) == ERROR)
		return (ERROR);
	return (CONTINUE);
}

int	take_forks_and_check_fin(t_info *info, t_philo *philo)
{
	if (info->num_of_philos % 2 == 1
		&& (philo->id == 1 || info->num_of_philos == philo->id))
		return (take_forks_in_case_first_or_last_person(philo));
	else if (philo->id % 2 == 0)
		return (take_forks_in_case_even_person(philo));
	else if (philo->id % 2 == 1)
		return (take_forks_in_case_odd_person(philo));
	return (FORK_ERROR);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&g_fork[philo->right_fork]);
	pthread_mutex_unlock(&g_fork[philo->left_fork]);
}
