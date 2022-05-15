#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>

# define GREEN "\033[0;32m"
# define RED "\033[1;31m"
# define YELLOW "\033[1;33m"
# define PURPLE "\033[0;35m"
# define BLUE "\033[0;34m"
 #define RESET "\033[0m"

typedef struct s_philo
{
	int				n;
	// int				time_die;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				nbr_left_fork;
	int				nbr_right_fork;
}	t_philo;

typedef struct s_data
{
	int				p;
	pthread_mutex_t	*forks;
	t_philo			*philo;
	// int				time_eat;
	// int				time_sleep;
}	t_data;

void*	take_forks(void *arg);
void*	eat(void *arg);
void*	sleeping(void *arg);

#endif