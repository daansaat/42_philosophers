/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:22:43 by dsaat         #+#    #+#                 */
/*   Updated: 2022/06/09 19:28:34 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static void	print_final(char *str, char *color, int n, t_data *data, int *var)
{
	if (!data->has_died && !data->done_eating)
		printf("%ldms %sP%d %s\n%s", ft_time() - \
		data->time_start, color, n + 1, str, RESET);
	*var = 1;
}

void	meals_monitor(t_philo *philo)
{
	philo->data->fed += 1;
	if (philo->data->fed == philo->data->p)
	{
		print_final("is eating", GREEN, philo->n, \
		philo->data, &philo->data->done_eating);
	}
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
			pthread_mutex_lock(&data->mutex);
			if (ft_time() - data->philo[i].time_last_meal > data->time_die)
				print_final("has died", RED, i, data, &data->has_died);
			pthread_mutex_unlock(&data->mutex);
		}
	}
	return (0);
}
