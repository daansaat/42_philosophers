/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:22:40 by dsaat         #+#    #+#                 */
/*   Updated: 2022/06/11 10:30:18 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>

# define RED "\033[1;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define TEAL "\033[0;36m"
# define RESET "\033[0m"

struct	s_data;

typedef struct s_philo
{
	int				n;
	int				lfork;
	int				rfork;
	int				meals;
	long			time_last_meal;
	long			time_now;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	int				p;
	int				fed;
	int				done;
	long			time_start;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	pthread_t		*threads;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex;
	t_philo			*philo;
}				t_data;

int		init_struct(char **argv, t_data *data);
int		init_mutex(t_data *data);
int		init_threads(t_data *data);

void	*dining(void *arg);
void	death_monitor(t_data *data);
void	meals_monitor(t_philo *philo);

long	ft_time(void);
int		ft_atoi(const char *str);
int		ft_is_digit(char **argv);
int		check_if_done(t_data *data);
int		ft_input_help(void);

#endif