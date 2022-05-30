#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <semaphore.h>

# define GREEN "\033[0;32m"
# define RED "\033[1;31m"
# define YELLOW "\033[1;33m"
# define PURPLE "\033[0;35m"
# define BLUE "\033[0;34m"
# define TEAL "\033[0;36m"
# define RESET "\033[0m"

typedef struct	s_data
{
	int		p;
    int     n;
	int		meals;
	int		done_eating;
	long	time_start;
	long	time_last_meal;
	long	time_die;
	long	time_eat;
	long	time_sleep;
	pid_t	*pid_child;
	sem_t   *fork_id;
	sem_t	*max_eating_id;
    sem_t   *print_id;
	sem_t	*meals_id;
	sem_t	*done_eating_id;
	sem_t	*death_id;
}				t_data;

void    init_struct(t_data *data, char **argv);
void    init_semaphore(t_data *data);
void    init_processes(t_data *data);

void    ft_parent_monitor(t_data *data);
void    ft_child_process(t_data *data);

int		ft_atoi(const char *str);
int		ft_is_digit(char **argv);
long	ft_time(void);
void	print_state(char *str, char *color, t_data *data);
void 	ft_error(char *str);
void	ft_check(int return_value);

#endif