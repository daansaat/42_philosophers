/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:22:43 by dsaat         #+#    #+#                 */
/*   Updated: 2022/06/03 14:28:42 by dsaat         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	meals_monitor(t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&philo->data->print);
	if (!philo->data->has_died)
	{
		i = 0;
		printf("%ldms %sP%d is eating\n%s", ft_time() - \
		philo->data->time_start, GREEN, philo->n + 1, RESET);
		philo->time_print = ft_time();
		while (philo->data->philo[i].meals == 0 && i < philo->data->p)
			i++;
		if (i == philo->data->p)
			philo->data->done_eating = 1;
	}
	pthread_mutex_unlock(&philo->data->print);
}

void	*death_monitor(void *arg)
{
	t_data	*data;
	long	time;
	int		i;

	data = (t_data *)arg;
	while (!data->has_died && !data->done_eating)
	{
		i = -1;
		while (!data->has_died && ++i < data->p)
		{
			time = ft_time();
			if (time - data->philo[i].time_last_meal > data->time_die)
			{
				pthread_mutex_lock(&data->print);
				if (!data->done_eating)
				{
					printf("%ldms %sP%d has died\n%s", ft_time() - \
					data->time_start, RED, data->philo[i].n + 1, RESET);
					data->has_died = 1;
				}
				pthread_mutex_unlock(&data->print);
			}
		}
	}
	return (0);
}
