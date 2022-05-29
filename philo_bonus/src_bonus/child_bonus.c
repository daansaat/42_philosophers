#include "philo_bonus.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

static void	sleeping(t_data *data)
{
	print_state("is sleeping", YELLOW, data);
	usleep(data->time_sleep);
	print_state("is thinking", PURPLE, data);
}

static void	eating(t_data *data)
{
	data->time_last_meal = ft_time();
	if (data->meals > 0)
		data->meals -= 1;
	if (data->meals == 0 && !data->done_eating)
	{
		data->done_eating = 1;
		ft_check(sem_wait(data->print_id));
		printf("%s%ldms %sP%d is eating\n%s", RESET, ft_time() - \
		data->time_start, GREEN, data->n + 1, RESET);
		ft_check(sem_post(data->meals_id));
		ft_check(sem_wait(data->done_eating_id));
		ft_check(sem_post(data->print_id));
	}
	else
    	print_state("is eating", GREEN, data);
	usleep(data->time_eat);
}

static void	take_forks(t_data *data)
{
    ft_check(sem_wait(data->max_eating_id));
	ft_check(sem_wait(data->fork_id));
	print_state("has taken a fork", BLUE, data);
    ft_check(sem_wait(data->fork_id));
	print_state("has taken a fork", BLUE, data);
	eating(data);
    ft_check(sem_post(data->fork_id));
    ft_check(sem_post(data->fork_id));
	ft_check(sem_post(data->max_eating_id));
}

static void*	death_monitor(void *arg)
{
	t_data	*data;
	long	time;

	data = (t_data *)arg;
	while (1)
	{
		ft_check(sem_wait(data->print_id));
		time = ft_time();
		if (time - data->time_last_meal > data->time_die)
		{
			printf("%s%ldms %sP%d has died\n%s", RESET, time - \
			data->time_start, RED, data->n + 1, RESET);
			ft_check(sem_post(data->death_id));
			break ;
		}
		ft_check(sem_post(data->print_id));
	}
	return (0);
}

void    ft_child_process(t_data *data)
{
    pthread_t	death;

	if (pthread_create(&death, NULL, &death_monitor, (void*)data) != 0)
		ft_error("pthread_create() failed");
	if (pthread_detach(death) != 0)
		ft_error("pthread_detach() failed");
    while (1)
    {
        take_forks(data);
        sleeping(data);
    }
}
