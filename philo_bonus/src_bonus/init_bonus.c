#include "philo_bonus.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

void    init_struct(t_data *data, char **argv)
{
    data->p = ft_atoi(argv[1]);
	data->time_start = ft_time();
	data->time_last_meal = data->time_start;
	data->meals = -1;
	data->done_eating = 0;
	data->has_died = 0;
	if (argv[5])
		data->meals = ft_atoi(argv[5]);
	data->time_die = ft_atoi(argv[2]) * 1000;
	data->time_eat = ft_atoi(argv[3]) * 1000;
	data->time_sleep = ft_atoi(argv[4]) * 1000;
	data->pid_child = malloc(sizeof(int) * data->p);
}

static void	ft_sem_error(char *str, t_data *data)
{
	sem_unlink(str);
	printf("Failed to create %s semaphore\n", str);
	if (data->fork_id == SEM_FAILED && data->print_id == SEM_FAILED \
	&& data->meals_id == SEM_FAILED && data->death_id == SEM_FAILED \
	&& data->done_eating_id)
		exit(0);
}

void    init_semaphore(t_data *data)
{
    data->fork_id = sem_open("/fork", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, data->p);
    if (data->fork_id == SEM_FAILED)
		ft_sem_error("/fork", data);
	data->print_id = sem_open("/print", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);
	if (data->print_id == SEM_FAILED)
		ft_sem_error("/print", data);
	data->meals_id = sem_open("/meals", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);
	if (data->meals_id == SEM_FAILED)
		ft_sem_error("/meals", data);
	data->done_eating_id = sem_open("/done_eating", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);
	if (data->done_eating_id == SEM_FAILED)
		ft_sem_error("/done_eating", data);
	data->death_id = sem_open("/death", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, data->p);
	if (data->death_id == SEM_FAILED)
		ft_sem_error("/death", data);
	sem_wait(data->meals_id);
	sem_wait(data->death_id);
}

void    init_processes(t_data *data)
{
    int	pid;
    int	philosopher;

    pid = 1;
	philosopher = 0;
    ft_parent(data);
	while (philosopher < data->p && pid != 0)
	{
		data->n = philosopher;
		pid = fork();
		if (pid == 0)
			ft_child(data);
		else
			data->pid_child[philosopher] = pid;
			philosopher++;

	}
	data->pid_child[philosopher] = '\0';
}
