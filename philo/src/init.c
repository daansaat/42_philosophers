/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:22:28 by dsaat         #+#    #+#                 */
/*   Updated: 2022/06/11 10:48:34 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

static int	ft_stop(t_data *data, int i, int j, char *str)
{
	if (i > 0)
	{
		pthread_mutex_lock(&data->mutex);
		data->done = 1;
		pthread_mutex_unlock(&data->mutex);
	}
	while (i > 0)
		pthread_join(data->threads[--i], NULL);
	while (j > 0)
		pthread_mutex_destroy(&data->forks[--j]);
	if (data->threads)
		free(data->threads);
	if (data->forks)
		free(data->forks);
	if (data->philo)
		free(data->philo);
	if (str)
	{
		printf("%s\n", str);
		return (1);
	}
	return (0);
}

static void	init_philo(char **argv, t_data *data)
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

int	init_struct(char **argv, t_data *data)
{
	data->p = ft_atoi(argv[1]);
	data->threads = malloc(sizeof(pthread_t) * data->p);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->p);
	data->philo = malloc(sizeof(t_philo) * data->p);
	if (!data->threads || !data->forks || !data->philo)
		return (ft_stop(data, 0, 0, "malloc() failed"));
	data->fed = 0;
	data->done = 0;
	data->time_start = ft_time();
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	init_philo(argv, data);
	return (0);
}

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->p)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (ft_stop(data, 0, i, "pthread_mutex_init() failed"));
		i++;
	}
	if (pthread_mutex_init(&data->mutex, NULL) != 0)
		return (ft_stop(data, 0, i, "pthread_mutex_init failed() failed"));
	return (0);
}	

int	init_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->p)
	{
		if (pthread_create(&data->threads[i], NULL, &dining, \
		(void *)&data->philo[i]) != 0)
			return (ft_stop(data, i, data->p, "pthead_create() failed"));
		i++;
	}
	if (data->p == 1)
		pthread_detach(data->threads[0]);
	death_monitor(data);
	ft_stop(data, i, i, NULL);
	return (0);
}
