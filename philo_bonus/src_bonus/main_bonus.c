#include "philo_bonus.h"
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// static void clean_up(t_data *data)
// {
//     printf("%s", RESET);
//     sem_unlink("/fork");
//     sem_unlink("/print");
//     sem_unlink("/meals");
//     sem_unlink("/done_eating");
//     sem_unlink("/death");
//     sem_close(data->fork_id);
//     sem_close(data->print_id);
//     sem_close(data->meals_id);
//     printf("SUCCES!!!\n");
//     sem_close(data->done_eating_id);
//     sem_close(data->death_id);
//     free(data->pid_child);
// }



int main(int argc, char **argv)
{
    t_data  data;

    (void)argc;
    init_struct(&data, argv);
    init_semaphore(&data);
    init_processes(&data);
    while (!data.done_eating && !data.has_died)
        usleep(1);
    printf("%s SUCCESS!!\n", RESET);
    // clean_up(&data);
    // while(waitpid(-1, NULL, 0) > 0)
    // system("leaks philo_bonus");
    return (0);
}