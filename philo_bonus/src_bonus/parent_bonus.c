#include "philo_bonus.h"
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

static void kill_children(t_data *data)
{
    int i;

    i = 0;
    while (data->pid_child[i])
    {
        // printf("%d\n", data->pid_child[i]);
        if (kill(data->pid_child[i], SIGKILL) != 0)
            ft_error("kill() failed");
        i++;
    }
}

void* meals_monitor(void *arg)
{
    t_data  *data;
    int     philosophers;

    data = (t_data *)arg;
    philosophers = data->p;
    while (philosophers)
    {
        sem_wait(data->meals_id);
        philosophers--;
    }
    kill_children(data);
    sem_post(data->meals_id);
    sem_post(data->death_id);
    sem_post(data->print_id);
    data->done_eating = 1;
    return (0);
}

static void*   death_monitor(void *arg)
{
    t_data  *data;

    data = (t_data *)arg;
    sem_wait(data->death_id);
    sem_post(data->meals_id);
    sem_post(data->death_id);
    sem_post(data->print_id);
    data->has_died = 1;
    kill_children(data);
    return (0);
}

void    ft_parent(t_data *data)
{
    pthread_t   meals;
    pthread_t   death;

    if (pthread_create(&meals, NULL, &meals_monitor, (void *)data) != 0)
        ft_error("pthread_create() failed");
    if (pthread_detach(meals) != 0)
        ft_error("pthread_detach() failed");
    if (pthread_create(&death, NULL, &death_monitor, (void *)data) != 0)
        ft_error("pthread_create() failed");
    if (pthread_detach(death) != 0)
        ft_error("pthread_detach() failed");
}