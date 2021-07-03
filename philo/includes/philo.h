#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define STATUS_SUCCESS					0
# define STATUS_ERROR					1

# define SUCCESS						1
# define ERROR							-1

# define TRUE							1
# define FALSE							0

# define FORK							0
# define EAT							1
# define SLEEP							2
# define THINK							3
# define DIE							4

# define INVALID_ARGUMENT				"invalid argument"
# define ONLY_ONE_PHILO					"only one philosoher"
# define MALLOC_FAILED					"malloc failed"
# define GETTIMEOFDAY_FAILED			"gettimeofday failed"
# define MALLOC_OR_GETTIMEOFDAY_FAILED	"malloc or gettimeofday failed"
# define PTHREAD_CREATE_FAILED			"pthread create failed"

typedef struct s_info
{
	int			num_of_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_of_each_eating;
}				t_info;

typedef struct s_philo
{
	int			id;
	int			count_eat;
	int			flag_eat_fin;
	int			flag_fin;
	long		time_last_eat;
	int			right_fork;
	int			left_fork;
	pthread_t	thread;
	pthread_t	watcher;
	t_info		*info;
}				t_philo;

/* init.c */
int			init_info(t_info *info, int argc, char **argv);
int			init_global_variables(t_info *info);
t_philo		*init_philo(t_info *info);


/* get_time.c */
long		get_time_in_ms(void);

/* print.c */
int			print_error_message(char *str);
void		print_status(t_philo *philo, int status);

/* thread.c */
int			create_threads(t_info *info, t_philo *philos);
void		join_threads(t_info *info, t_philo *philos);

/* philo_life.c */
void		*philo_life(void *arg);

/* eat.c */
void		take_forks(t_philo *philo);
void		drop_forks(t_philo *philo);
int			eat_spaghetti(t_info *info, t_philo *philo);

/* sleep_think.c */
int			spend_sleeping(t_info *info, t_philo *philo);
void		think_deeply(t_philo *philo);

/* watcher.c */
void		*watcher(void *arg);

/* utils.c */
int 		check_arguments(int argc, char **argv);
int			is_integer(int sign, char *number);
int 		is_number(char *str);

/* libft.c */
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *str);

extern pthread_mutex_t	*g_fork;
extern pthread_mutex_t	g_print;//いらないかも
extern pthread_mutex_t	g_die;
extern pthread_t		g_watcher;
extern int				g_flag_fin;

#endif