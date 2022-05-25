#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <pthread.h>
# define FORK "/fork"
// typedef struct s_philo
// {
// 	int				n;
// 	int				lfork;
// 	int				rfork;
// 	int				meals;
// 	long			time_last_meal;
// 	struct s_data	*data;
// }					t_philo;

typedef struct s_data
{
	int				p;
    int             n;
	// int				has_died;
	// int				done_eating;
	long			time_start;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	pthread_t		*threads;
	pthread_t		monitor;
	// t_philo			*philo;

}					t_data;

int	ft_atoi(const char *str);

#endif