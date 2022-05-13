#ifndef PHILO_H
# define PHILO_H

typedef struct s_philo
{
	int				n;
	// int				time_die;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

typedef struct s_data
{
	int				p;
	pthread_mutex_t	*forks;
	t_philo			*philo;
	// int				time_eat;
	// int				time_sleep;
}	t_data;

#endif