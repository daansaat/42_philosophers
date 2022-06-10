/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:22:43 by dsaat         #+#    #+#                 */
/*   Updated: 2022/06/10 18:31:42 by dsaat         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static void	print_final(char *str, char *color, t_philo *philo, int *var)
{
	if (!philo->data->has_died && !philo->data->done_eating)
		printf("%ldms %sP%d %s\n%s", ft_time() - philo->data->time_start, \
		color, philo->n + 1, str, RESET);
	*var = 1;
}

void	meals_monitor(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex);
	philo->meals -= 1;
	if (philo->meals == 0)
		philo->data->fed += 1;
	if (philo->data->fed == philo->data->p)
		print_final("is eating", GREEN, philo, &philo->data->done_eating);
	philo->time_last_meal = ft_time();
	pthread_mutex_unlock(&philo->data->mutex);
}

void	death_monitor(t_data *data)
{
	int		i;

	while (!check_if_done(data))
	{
		i = -1;
		while (!data->has_died && ++i < data->p)
		{
			pthread_mutex_lock(&data->mutex);
			if (ft_time() - data->philo[i].time_last_meal > data->time_die)
				print_final("has died", RED, &data->philo[i], &data->has_died);
			pthread_mutex_unlock(&data->mutex);
		}
	}
}
