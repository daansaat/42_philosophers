/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:22:28 by dsaat         #+#    #+#                 */
/*   Updated: 2022/06/07 12:25:08 by dsaat         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

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
	if (!data->threads || !data->monitor || !data->forks || !data->philo)
		return (1);
	data->time_start = ft_time();
	data->has_died = 0;
	data->done_eating = 0;
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
			return (ft_error("pthread_mutex_init() failed"));
		i++;
	}
	if (pthread_mutex_init(&data->print, NULL) != 0)
		return (ft_error("pthread_mutex_init failed() failed"));
	if (pthread_mutex_init(&data->meals_monitor, NULL) != 0)
		return (ft_error("pthread_mutex_init failed() failed"));
	return (0);
}	

int	init_monitor(t_data *data)
{
	if (pthread_create(&data->monitor, NULL, &death_monitor, \
	(void *)data) != 0)
		return (ft_error("pthead_create() failed"));
	pthread_detach(data->monitor);
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
			return (ft_error("pthead_create() failed"));
		i++;
	}
	i = 0;
	while (i < data->p)
	{
		pthread_join(data->threads[i], NULL);
		i++;
	}
	return (0);
}
