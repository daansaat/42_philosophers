#include "philo_bonus.h"
#include <stdio.h>
#include <signal.h>
#include <pthread.h>

static void kill_children(t_data *data)
{
    int i;

    i = 0;
    while (data->pid_child[i])
    {
        if (kill(data->pid_child[i], SIGKILL) != 0)
            ft_error("kill() failed");
        data->pid_child[i] = 0;
        i++;
    }
    printf("%s", RESET);
}

static void	*meals_monitor(void *arg)
{
    t_data  *data;
    int     philo;

    data = (t_data *)arg;
    philo = data->p;
    while (philo)
    {
        ft_check(sem_wait(data->meals_id));
        philo--;
    }
    ft_check(sem_close(data->meals_id));
    kill_children(data);
    return (0);
}

static void	*death_monitor(void *arg)
{
    t_data  *data;

    data = (t_data *)arg;
    ft_check(sem_wait(data->death_id));
    ft_check(sem_close(data->death_id));
    kill_children(data);
    return (0);
}

void    ft_parent_monitor(t_data *data)
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