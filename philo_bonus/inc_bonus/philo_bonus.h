#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
// # include <pthread.h>
#include <semaphore.h>

# define GREEN "\033[0;32m"
# define RED "\033[1;31m"
# define YELLOW "\033[1;33m"
# define PURPLE "\033[0;35m"
# define BLUE "\033[0;34m"
# define TEAL "\033[0;36m"
# define RESET "\033[0m"
// # define FORK "/fork"
// # define PRINT
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
	int				meals;
	int				done_eating;
	int				has_died;
	long			time_start;
	long			time_last_meal;
	// int				has_died;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	int				*pid_child;
	// pthread_t		*threads;
	// pthread_t		monitor;
	sem_t   		*fork_id;
    sem_t   		*print_id;
	sem_t			*meals_id;
	sem_t			*done_eating_id;
	sem_t			*death_id;

	// t_philo			*philo;

}					t_data;

void    init_struct(t_data *data, char **argv);
void    init_semaphore(t_data *data);
void    init_processes(t_data *data);

void    ft_child(t_data *data);
void    ft_parent(t_data *data);

long	ft_time(void);
void	print_state(char *str, char *color, t_data *data);
int		ft_atoi(const char *str);
void 	ft_error(char *str);

#endif