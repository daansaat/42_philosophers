#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>

# define GREEN "\033[0;32m"
# define RED "\033[1;31m"
# define YELLOW "\033[1;33m"
# define PURPLE "\033[0;35m"
# define BLUE "\033[0;34m"
 #define RESET "\033[0m"

struct s_data;

typedef struct s_philo
{
	int				n;
	int				lfork;
	int				rfork;
	int				meals;
	long			time_last_meal;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				p;
	int				has_died;
	long			time_start;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	pthread_mutex_t	*forks;
	pthread_mutex_t print;
	t_philo			*philo;

}					t_data;

void	init_struct(char **argv, t_data *data);
void	init_threads(t_data *data);

void*	dining(void *arg);
void*	take_forks(void *arg);
void*	eating(void *arg);
void*	sleeping(void *arg);

void	death_monitor(t_data *data);
void	print_state(char *str, char *color, t_philo *philo);
long	ft_time(void);


#endif