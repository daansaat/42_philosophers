/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:22:43 by dsaat         #+#    #+#                 */
/*   Updated: 2022/06/09 08:53:09 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static void	print_final(char *str, char *color, int n, t_data *data, int *var)
{
	pthread_mutex_lock(&data->done);
	if (!data->has_died && !data->done_eating)
	{
		pthread_mutex_lock(&data->print);
		printf("%ldms %sP%d %s\n%s", ft_time() - \
		data->time_start, color, n + 1, str, RESET);
		*var = 1;
		pthread_mutex_unlock(&data->print);
	}
	pthread_mutex_unlock(&data->done);	
}

void	meals_monitor(t_philo *philo)
{
	int	i;

	i = 0;
	while (philo->data->philo[i].meals <= 0 && i < philo->data->p)
		i++;
	if (i == philo->data->p)
		print_final("is eating", GREEN, philo->n, \
		philo->data, &philo->data->done_eating);
}

void	*death_monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!check_if_done(data))
	{
		i = -1;
		while (!data->has_died && ++i < data->p)
		{
			pthread_mutex_lock(&data->time_last_meal[i]);
			if (ft_time() - data->philo[i].time_last_meal > data->time_die)
				print_final("has died", RED, i, data, &data->has_died);
			pthread_mutex_unlock(&data->time_last_meal[i]);
		}
	}
	return (0);
}
