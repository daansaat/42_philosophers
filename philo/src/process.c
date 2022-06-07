/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:22:46 by dsaat         #+#    #+#                 */
/*   Updated: 2022/06/07 12:11:53 by dsaat         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static void	precise_sleep(t_philo *philo, long time)
{
	while (!philo->data->has_died && !philo->data->done_eating)
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
	while (!philo->data->has_died && !philo->data->done_eating)
	{
		print_state("is thinking", PURPLE, philo);
		take_forks(philo);
		pthread_mutex_lock(&philo->data->meals_monitor);
		if (philo->meals > 0)
			philo->meals -= 1;
		if (philo->meals == 0 && !philo->data->done_eating)
			meals_monitor(philo);
		else
			print_state("is eating", GREEN, philo);
		pthread_mutex_unlock(&philo->data->meals_monitor);
		philo->time_last_meal = ft_time();
		precise_sleep(philo, philo->data->time_eat);
		print_state("is sleeping", YELLOW, philo);
		pthread_mutex_unlock(&philo->data->forks[philo->lfork]);
		pthread_mutex_unlock(&philo->data->forks[philo->rfork]);
		precise_sleep(philo, philo->data->time_sleep);
	}
	return (0);
}
