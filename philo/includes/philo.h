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

# define STDERR							2

# define CONTINUE						0
# define FINISH							1

# define FORK							0
# define EAT							1
# define SLEEP							2
# define THINK							3
# define DIE							4

# define INVALID_ARGUMENT				"invalid argument"
# define TOO_MANY_PHILO					"too many philosophers"
# define MALLOC_FAILED					"malloc failed"
# define GETTIMEOFDAY_FAILED			"gettimeofday failed"
# define MALLOC_OR_GETTIMEOFDAY_FAILED	"malloc or gettimeofday failed"
# define PTHREAD_CREATE_FAILED			"pthread create failed"

typedef struct s_info
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_each_eating;
	int				count_all_eat;
}					t_info;

typedef struct s_philo
{
	int				id;
	int				count_eat;
	int				flag_eat_fin;
	long			time_last_eat;
	int				right_fork;
	int				left_fork;
	pthread_t		thread;
	pthread_t		watcher;
	pthread_mutex_t	die;
	t_info			*info;
}					t_philo;

/* init.c */
int			init_info(t_info *info, int argc, char **argv);
int			init_global_variables(t_info *info);
t_philo		*init_philo(t_info *info);

/* get_time.c */
long		get_time_in_ms(void);

/* print.c */
int			print_status_and_check_fin(t_philo *philo, int status);
int			print_error_message(char *str);

/* thread.c */
int			create_threads(t_info *info, t_philo *philos);
void		join_threads(t_info *info, t_philo *philos);

/* philo_life.c */
void		*philo_life(void *arg);

/* eat.c */
int			take_forks_and_check_fin(t_philo *philo);
void		drop_forks(t_philo *philo);
int			eat_spaghetti(t_info *info, t_philo *philo);

/* check_count.c */
void		check_count_eat(t_info *info, t_philo *philo);

/* sleep_think.c */
int			spend_sleeping(t_info *info, t_philo *philo);
int			think_deeply(t_philo *philo);

/* watcher.c */
void		*death_watcher(void *arg);
void		switch_flag_to_fin(void);

/* utils.c */
int			check_arguments(int argc, char **argv);
int			is_integer(int sign, char *number);
int			is_positive_number(char *str);

/* libft.c */
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *str);

extern pthread_mutex_t	*g_fork;
extern pthread_mutex_t	g_print;
extern pthread_mutex_t	g_fin;
extern pthread_mutex_t	g_eat;
extern int				g_flag_fin;

#endif