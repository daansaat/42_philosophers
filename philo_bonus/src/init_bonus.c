/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_bonus.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:23:00 by dsaat         #+#    #+#                 */
/*   Updated: 2022/06/11 22:00:48 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <unistd.h>
#include <string.h>

void	init_struct(t_data *data)
{
	data->time_start = ft_time();
	data->time_last_meal = data->time_start;
	data->pid_child = malloc(sizeof(pid_t) * (data->p + 1));
	if (!data->pid_child)
		ft_error(data, "malloc() failed");
	memset(data->pid_child, 0, sizeof(pid_t) * (data->p + 1));
}

void	init_semaphore(t_data *data)
{
	data->fork_id = sem_open("/fork",
			O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, data->p);
	if (data->fork_id)
		sem_unlink("/fork");
	data->can_sit_id = sem_open("/can_sit",
			O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, data->p / 2);
	if (data->can_sit_id)
		sem_unlink("/can_sit");
	data->mutex_id = sem_open("/mutex",
			O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);
	if (data->mutex_id)
		sem_unlink("/mutex");
	data->done_eating_id = sem_open("/done_eating",
			O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);
	if (data->done_eating_id)
		sem_unlink("/done_eating");
	if (data->fork_id == SEM_FAILED || data->mutex_id == SEM_FAILED \
	|| data->done_eating_id == SEM_FAILED || data->can_sit_id == SEM_FAILED)
		ft_error(data, "sem_open() failed");
}

void	init_processes(t_data *data)
{
	int	philo;

	philo = 0;
	while (philo < data->p)
	{
		data->n = philo;
		data->pid_child[philo] = fork();
		if (data->pid_child[philo] == -1)
			ft_error(data, "fork() failed");
		if (data->pid_child[philo] == 0)
			ft_child_process(data);
		philo++;
	}
	ft_parent_process(data);
}
