#include "philo_bonus.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <semaphore.h>

void    init_threads(t_data *data)
{
    sem_t   *fork_id;

    (void)data;
    fork_id = sem_open(FORK, 0);
    if (fork_id == SEM_FAILED)
        printf("sem_open() FORK on child failed");
	while (1)
	{
    if (sem_wait(fork_id) < 0)
        printf("sem_wait() failed\n");
    if (sem_wait(fork_id) < 0)
        printf("sem_wait() failed\n");
    printf("hello from P%d\n", data->n);
    // usleep(1000000);
    if (sem_post(fork_id) < 0)
        printf("sem_post() failed\n");
    if (sem_post(fork_id) < 0)
        printf("sem_post() failed\n");
	}
}

void    init_processes(t_data *data)
{
    int	pid;
    int	philosopher;

    pid = 1;
	philosopher = 1;
        while (data->p > 0 && pid != 0)
        {
            data->n = philosopher;
			pid = fork();
            data->p -= 1;
			philosopher += 1;
        }
    if (pid == 0)
        init_threads(data);
}

void    init_struct(t_data *data, char **argv)
{
    data->p = ft_atoi(argv[1]);
}

void    init_sem(t_data *data)
{
    (void)data;
    sem_t   *fork_id;
    fork_id = sem_open(FORK, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, data->p);
    if (fork_id == SEM_FAILED)
	{
		sem_unlink(FORK);
        printf("Failed to create fork semaphore\n");
	}
    sem_close(fork_id);
}

int main(int argc, char **argv)
{
    t_data  data;

    (void)argc;
    init_struct(&data, argv);
    init_sem(&data);
    init_processes(&data);
    while(waitpid(-1, NULL, 0) > 0)
    sem_unlink(FORK);
    return (0);

}