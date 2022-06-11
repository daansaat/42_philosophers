/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:22:43 by dsaat         #+#    #+#                 */
/*   Updated: 2022/06/11 09:06:41 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static void	print_final(char *str, char *color, t_philo *philo)
{
	if (!philo->data->done)
		printf("%ldms %sP%d %s\n%s", ft_time() - philo->data->time_start, \
		color, philo->n + 1, str, RESET);
	philo->data->done = 1;
}

void	meals_monitor(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex);
	philo->meals -= 1;
	if (philo->meals == 0)
		philo->data->fed += 1;
	if (philo->data->fed == philo->data->p)
		print_final("is eating", GREEN, philo);
	philo->time_last_meal = ft_time();
	pthread_mutex_unlock(&philo->data->mutex);
}

void	death_monitor(t_data *data)
{
	int		i;
	int		done;

	done = 0;
	while (!done)
	{
		i = -1;
		while (!done && ++i < data->p)
		{
			pthread_mutex_lock(&data->mutex);
			if (ft_time() - data->philo[i].time_last_meal > data->time_die)
				print_final("has died", RED, &data->philo[i]);
			done = data->done;
			pthread_mutex_unlock(&data->mutex);
		}
	}
}
