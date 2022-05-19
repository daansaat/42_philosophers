#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

int	init_struct(char **argv, t_data *data)
{
	data->p = ft_atoi(argv[1]);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->p);
	data->philo = malloc(sizeof(t_philo) * data->p);
	if (!data->forks || !data->philo)
		return (0);
	data->time_start = ft_time();
	data->has_died = 0;
	data->done_eating = 0;
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	return (0);
}

void	init_philo(char **argv, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->p)
	{
		data->philo[i].n = i;
		data->philo[i].lfork = i;
		data->philo[i].rfork = (i + 1) % data->p;
		data->philo[i].meals = -1;
		if (argv[5])
			data->philo[i].meals = ft_atoi(argv[5]);
		data->philo[i].time_last_meal = data->time_start;
		data->philo[i].data = data;
		i++;
	}
}

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->p)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->print, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->meals_monitor, NULL) != 0)
		return (1);
}	

int	init_threads(t_data *data)
{
	pthread_t		*threads;
	int				i;
	
	threads = malloc(sizeof(pthread_t) * data->p);
	if (!threads)
		return (0);
	i = 0;
	while (i < data->p)
	{
		if (pthread_create(&threads[i], NULL, &dining, \
		(void*)&data->philo[i]) != 0)
			return (0);
		i++;
	}
	death_monitor(data);
	i = 0;
	while (i < data->p)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (0);
		i++;
	}
	free(threads);
	return (0);
}