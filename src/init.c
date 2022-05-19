#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

void	init_struct(char **argv, t_data *data)
{
	int	i;

	data->p = ft_atoi(argv[1]);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->p);
	data->philo = malloc(sizeof(t_philo) * data->p);
	data->time_start = ft_time();
	data->has_died = 0;
	data->done_eating = 0;
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
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

void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->p)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print, NULL);
}	

void	init_threads(t_data *data)
{
	pthread_t		*threads;
	pthread_t		monitor;
	int				i;
	
	threads = malloc(sizeof(pthread_t) * data->p);
	i = 0;
	while (i < data->p)
	{
		if (pthread_create(&threads[i], NULL, &dining, (void*)&data->philo[i]) != 0)
			return ;
		i++;
	}
	i = 0;
	pthread_create(&monitor, NULL, &meals_monitor, (void*)data);
	death_monitor(data);
	while (i < data->p)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return ;
		i++;
	}
	pthread_join(monitor, NULL);
}