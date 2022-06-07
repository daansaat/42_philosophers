/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   child_bonus.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:22:57 by dsaat         #+#    #+#                 */
/*   Updated: 2022/06/07 12:23:39 by dsaat         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

static void	*death_monitor(void *arg)
{
	t_data	*data;
	long	time;

	data = (t_data *)arg;
	while (1)
	{
		sem_wait(data->print_id);
		time = ft_time();
		if (time - data->time_last_meal > data->time_die)
		{
			printf("%s%ldms %sP%d has died\n%s", RESET, time - \
			data->time_start, RED, data->n + 1, RESET);
			sem_post(data->death_id);
			break ;
		}
		sem_post(data->print_id);
	}
	return (0);
}

static void	eating(t_data *data)
{
	if (data->meals > 0)
		data->meals -= 1;
	if (data->meals == 0 && !data->done_eating)
	{
		data->done_eating = 1;
		sem_wait(data->print_id);
		printf("%s%ldms %sP%d is eating\n%s", RESET, ft_time() - \
		data->time_start, GREEN, data->n + 1, RESET);
		sem_post(data->meals_id);
		sem_wait(data->done_eating_id);
		sem_post(data->print_id);
	}
	else
		print_state("is eating", GREEN, data);
	data->time_last_meal = ft_time();
	while (ft_time() - data->time_print < data->time_eat)
		usleep(500);
}

void	ft_child_process(t_data *data)
{
	pthread_t	death;

	if (pthread_create(&death, NULL, &death_monitor, (void *)data) != 0)
		ft_error(data, "pthread_create() failed");
	pthread_detach(death);
	while (1)
	{
		print_state("is thinking", PURPLE, data);
		sem_wait(data->can_sit_id);
		sem_wait(data->fork_id);
		print_state("has taken a fork", BLUE, data);
		sem_wait(data->fork_id);
		print_state("has taken a fork", BLUE, data);
		eating(data);
		sem_post(data->fork_id);
		sem_post(data->fork_id);
		sem_post(data->can_sit_id);
		print_state("is sleeping", YELLOW, data);
		while (ft_time() - data->time_print < data->time_sleep)
			usleep(500);
	}
}
