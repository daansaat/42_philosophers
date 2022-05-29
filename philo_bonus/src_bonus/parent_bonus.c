#include "philo_bonus.h"
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

static void* meals_monitor(void *arg)
{
    t_data  *data;
    int     philo;

    data = (t_data *)arg;
    philo = data->p;
    while (philo)
    {
        sem_wait(data->meals_id);
        philo--;
    }
    sem_post(data->stop_id);
    return (0);
}

static void*   death_monitor(void *arg)
{
    t_data  *data;

    data = (t_data *)arg;
    sem_wait(data->death_id);
    sem_post(data->stop_id);
    return (0);
}

void    ft_parent_monitor(t_data *data)
{
    pthread_t   meals;
    pthread_t   death;

    if (pthread_create(&meals, NULL, &meals_monitor, (void *)data) != 0)
        ft_error(data, "pthread_create() failed");
    if (pthread_detach(meals) != 0)
        ft_error(data, "pthread_detach() failed");
    if (pthread_create(&death, NULL, &death_monitor, (void *)data) != 0)
        ft_error(data, "pthread_create() failed");
    if (pthread_detach(death) != 0)
        ft_error(data, "pthread_detach() failed");
}