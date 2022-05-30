#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>

# define GREEN "\033[0;32m"
# define RED "\033[1;31m"
# define YELLOW "\033[1;33m"
# define PURPLE "\033[0;35m"
# define BLUE "\033[0;34m"
# define TEAL "\033[0;36m"
# define RESET "\033[0m"

struct s_data;

typedef struct	s_philo
{
	int				n;
	int				lfork;
	int				rfork;
	int				meals;
	long			time_last_meal;
	struct s_data	*data;
}				t_philo;

typedef struct	s_data
{
	int				p;
	int				has_died;
	int				done_eating;
	long			time_start;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	pthread_t		*threads;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t print;
	pthread_mutex_t	meals_monitor;
	t_philo			*philo;

}				t_data;

int		init_struct(char **argv, t_data *data);
int		init_monitor(t_data *data);
int		init_threads(t_data *data);
int		init_mutex(t_data *data);

void*	dining(void *arg);
void*	death_monitor(void *arg);
void	meals_monitor(t_philo *philo);

int		ft_error(char *str);
int		ft_atoi(const char *str);
int		ft_is_digit(char **argv);
long	ft_time(void);
void	print_state(char *str, char *color, t_philo *philo);

#endif