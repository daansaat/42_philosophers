#include "philo_bonus.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>
#include <pthread.h>

void    init_struct(t_data *data, char **argv)
{
    data->p = ft_atoi(argv[1]);
	data->time_start = ft_time();
	data->time_last_meal = data->time_start;
	data->meals = -1;
	data->done_eating = 0;
	if (argv[5])
		data->meals = ft_atoi(argv[5]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]) * 1000;
	data->time_sleep = ft_atoi(argv[4]) * 1000;
	data->pid_child = malloc(sizeof(pid_t) * (data->p + 1));
	if (!data->pid_child)
		ft_error("malloc() failed");
	memset(data->pid_child, 0, sizeof(pid_t) * (data->p + 1));
}

void    init_semaphore(t_data *data)
{
	sem_unlink("/fork");
	sem_unlink("/can_sit");
    sem_unlink("/print");
    sem_unlink("/meals");
    sem_unlink("/done_eating");
    sem_unlink("/death");
	data->fork_id = sem_open("/fork", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, data->p);
	data->can_sit_id = sem_open("/can_sit", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, data->p / 2);
	data->print_id = sem_open("/print", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);
	data->meals_id = sem_open("/meals", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);
	data->done_eating_id = sem_open("/done_eating", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, data->p - 1);
	data->death_id = sem_open("/death", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);
    if (data->fork_id == SEM_FAILED || data->print_id == SEM_FAILED \
	|| data->meals_id == SEM_FAILED || data->done_eating_id == SEM_FAILED \
	|| data->death_id == SEM_FAILED || data->can_sit_id == SEM_FAILED)
		ft_error("sem_open() failed");
}

void    init_processes(t_data *data)
{
    int	philo;

	philo = 0;
	while (philo < data->p)
	{
		data->n = philo;
		data->pid_child[philo] = fork();
		if (data->pid_child[philo] == -1)
			ft_error("fork() failed");
		else if (data->pid_child[philo] == 0)
			ft_child_process(data);
		else
			philo++;
	}
    ft_parent_monitor(data);
}
