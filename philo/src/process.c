/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:22:46 by dsaat         #+#    #+#                 */
/*   Updated: 2022/06/09 08:52:41 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

#include <stdio.h>

int	check_if_done(t_data *data)
{
	pthread_mutex_lock(&data->done);
	if (data->has_died || data->done_eating)
	{
		pthread_mutex_unlock(&data->done);	
		return (1);
	}
	pthread_mutex_unlock(&data->done);	
	return (0);
}

static void	precise_sleep(t_philo *philo, long time)
{
	while (!check_if_done(philo->data))
	{
		if (ft_time() - philo->time_print >= time)
			break ;
		usleep(500);
	}
}

static void	take_forks(t_philo *philo)
{
	if (philo->n % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->rfork]);
		print_state("has taken a fork", BLUE, philo);
		pthread_mutex_lock(&philo->data->forks[philo->lfork]);
		print_state("has taken a fork", BLUE, philo);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->lfork]);
		print_state("has taken a fork", BLUE, philo);
		pthread_mutex_lock(&philo->data->forks[philo->rfork]);
		print_state("has taken a fork", BLUE, philo);
	}
}

void	*dining(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!check_if_done(philo->data))
	{
		print_state("is thinking", PURPLE, philo);
		take_forks(philo);
		pthread_mutex_lock(&philo->data->meals_monitor);
		philo->meals -= 1;
		if (philo->meals == 0)
			meals_monitor(philo);
		pthread_mutex_unlock(&philo->data->meals_monitor);
		print_state("is eating", GREEN, philo);
		pthread_mutex_lock(&philo->data->time_last_meal[philo->n]);
		philo->time_last_meal = ft_time();
		pthread_mutex_unlock(&philo->data->time_last_meal[philo->n]);
		precise_sleep(philo, philo->data->time_eat);
		print_state("is sleeping", YELLOW, philo);
		pthread_mutex_unlock(&philo->data->forks[philo->lfork]);
		pthread_mutex_unlock(&philo->data->forks[philo->rfork]);
		precise_sleep(philo, philo->data->time_sleep);
	}
	return (0);
}
