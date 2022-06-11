/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parent_bonus.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:23:06 by dsaat         #+#    #+#                 */
/*   Updated: 2022/06/11 14:34:08 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdio.h>
#include <signal.h>
#include <pthread.h>

void	terminate_children(t_data *data)
{
	int	i;

	i = 0;
	while (data->pid_child && data->pid_child[i])
	{
		kill(data->pid_child[i], SIGTERM);
		i++;
	}
	free(data->pid_child);
	printf("%s", RESET);
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
	terminate_children(data);
	return (0);
}

void	ft_parent_process(t_data *data)
{
	pid_t		pid;
	int			status;
	pthread_t	meals;

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
			terminate_children(data);
		if (WIFSIGNALED(status))
			break ;
	}
}
