/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:22:46 by dsaat         #+#    #+#                 */
/*   Updated: 2022/06/09 18:53:09 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

#include <stdio.h>

int	check_if_done(t_data *data)
{
	pthread_mutex_lock(&data->mutex);
	if (data->has_died || data->done_eating)
	{
		pthread_mutex_unlock(&data->mutex);	
		return (1);
	}
	pthread_mutex_unlock(&data->mutex);	
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
	// if (philo->n % 2 == 0)
	// {
		// pthread_mutex_lock(&philo->data->forks[philo->rfork]);
		// print_state("has taken a fork", BLUE, philo);
		// pthread_mutex_lock(&philo->data->forks[philo->lfork]);
		// print_state("has taken a fork", BLUE, philo);
	// }
	// else
	// {
		pthread_mutex_lock(&philo->data->forks[philo->lfork]);
		print_state("has taken a fork", BLUE, philo);
		pthread_mutex_lock(&philo->data->forks[philo->rfork]);
		print_state("has taken a fork", BLUE, philo);
	// }
}

void	*dining(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->n % 2 == 0)
		usleep(10000);
	while (!check_if_done(philo->data))
	{
		print_state("is thinking", PURPLE, philo);
		take_forks(philo);
		pthread_mutex_lock(&philo->data->mutex);
		philo->meals -= 1;
		if (philo->meals == 0)
			meals_monitor(philo);
		philo->time_last_meal = ft_time();
		pthread_mutex_unlock(&philo->data->mutex);
		print_state("is eating", GREEN, philo);
		precise_sleep(philo, philo->data->time_eat);
		pthread_mutex_unlock(&philo->data->forks[philo->lfork]);
		pthread_mutex_unlock(&philo->data->forks[philo->rfork]);
		print_state("is sleeping", YELLOW, philo);
		precise_sleep(philo, philo->data->time_sleep);
	}
	return (0);
}
