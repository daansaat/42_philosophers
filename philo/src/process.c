/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:22:46 by dsaat         #+#    #+#                 */
/*   Updated: 2022/06/11 21:50:49 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

static int	check_if_done(t_data *data)
{
	pthread_mutex_lock(&data->mutex);
	if (data->done)
	{
		pthread_mutex_unlock(&data->mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->mutex);
	return (0);
}

static void	precise_sleep(t_philo *philo, long time)
{
	usleep(time * 500);
	while (ft_time() - philo->time_now <= time)
		usleep(100);
}

static void	print_state(char *str, char *color, t_philo *philo)
{
	long	time_ms;

	pthread_mutex_lock(&philo->data->mutex);
	if (!philo->data->done)
	{
		time_ms = ft_time() - philo->data->time_start;
		printf("%ldms %sP%d %s\n%s", time_ms, color, philo->n + 1, str, RESET);
		philo->time_now = ft_time();
	}
	pthread_mutex_unlock(&philo->data->mutex);
}

void	*dining(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->n % 2 == 1)
		usleep(10000);
	while (!check_if_done(philo->data))
	{
		print_state("is thinking", PURPLE, philo);
		pthread_mutex_lock(&philo->data->forks[philo->lfork]);
		print_state("has taken a fork", BLUE, philo);
		pthread_mutex_lock(&philo->data->forks[philo->rfork]);
		print_state("has taken a fork", BLUE, philo);
		meals_monitor(philo);
		print_state("is eating", GREEN, philo);
		precise_sleep(philo, philo->data->time_eat);
		pthread_mutex_unlock(&philo->data->forks[philo->lfork]);
		pthread_mutex_unlock(&philo->data->forks[philo->rfork]);
		print_state("is sleeping", YELLOW, philo);
		precise_sleep(philo, philo->data->time_sleep);
	}
	return (0);
}
