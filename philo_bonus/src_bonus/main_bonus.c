#include "philo_bonus.h"
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// static void clean_up(t_data *data)
// {
//     sem_post(data->fork_id);
//     sem_post(data->print_id);
//     sem_post(data->meals_id);
//     sem_post(data->done_eating_id);
//     sem_post(data->death_id);
//     sem_post(data->stop_id);
//     sem_close(data->fork_id);
//     sem_close(data->print_id);
//     sem_close(data->meals_id);
//     sem_close(data->done_eating_id);
//     sem_close(data->death_id);
//     sem_close(data->stop_id);
//     free(data.pid_child);
// }

void kill_children(t_data *data)
{
    int i;

    i = 0;
    while (data->pid_child[i])
    {
        if (kill(data->pid_child[i], SIGKILL) != 0)
            ft_error(data, "kill() failed");
        i++;
    }
}

int main(int argc, char **argv)
{
    t_data  data;

    (void)argc;
    init_struct(&data, argv);
    init_semaphore(&data);
    init_processes(&data);
    kill_children(&data);
    // clean_up(&data);
    printf("%s", RESET);
    return (0);
}