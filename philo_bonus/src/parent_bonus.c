/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parent_bonus.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:23:06 by dsaat         #+#    #+#                 */
/*   Updated: 2022/06/22 13:19:14 by dsaat         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdio.h>
#include <signal.h>
#include <pthread.h>

void	ft_stop(t_data *data)
{
	int	i;

	i = 0;
	if (data->pid_child)
	{
		while (data->pid_child[i] && data->pid_child[i] != -1)
		{
			kill(data->pid_child[i], SIGTERM);
			i++;
		}
		free(data->pid_child);
	}
	printf("%s", RESET);
	exit(EXIT_SUCCESS);
}

static void	*meals_monitor(void *arg)
{
	t_data	*data;
	int		philo;

	data = (t_data *)arg;
	philo = data->p;
	while (philo)
	{
		sem_wait(data->done_eating_id);
		philo--;
		if (philo != 0)
			sem_post(data->mutex_id);
	}
	sem_close(data->done_eating_id);
	ft_stop(data);
	return (0);
}

void	ft_parent_process(t_data *data)
{
	pthread_t	meals;
	pid_t		pid;
	int			status;

	if (pthread_create(&meals, NULL, &meals_monitor, (void *)data) != 0)
		ft_error(data, "pthread_create() failed");
	if (pthread_detach(meals) != 0)
		ft_error(data, "pthread_detach() failed");
	while (1)
	{
		pid = waitpid(0, &status, 0);
		if (pid == -1)
			ft_error(data, "waitpid() failed");
		if (WEXITSTATUS(status) == -1)
			sem_post(data->mutex_id);
		if (WIFEXITED(status))
			ft_stop(data);
	}
}
