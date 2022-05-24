#include "philo.h"
#include <stdio.h>
#include <unistd.h>

static void	sleeping(t_philo *philo)
{
	print_state("is sleeping", YELLOW, philo);
	usleep(philo->data->time_sleep * 1000);
	print_state("is thinking", PURPLE, philo);
}

static void	eating(t_philo *philo)
{
	philo->time_last_meal = ft_time();
	pthread_mutex_lock(&philo->data->meals_monitor);
	if (philo->meals > 0)
		philo->meals -= 1;
	if (philo->meals == 0 && !philo->data->done_eating)
		meals_monitor(philo);
	else
		print_state("is eating", GREEN, philo);
	pthread_mutex_unlock(&philo->data->meals_monitor);
	usleep(philo->data->time_eat * 1000);
	pthread_mutex_unlock(&philo->data->forks[philo->lfork]);
	pthread_mutex_unlock(&philo->data->forks[philo->rfork]);
}

static void	free_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->lfork]);
	pthread_mutex_unlock(&philo->data->forks[philo->rfork]);
}

static void	take_forks(t_philo *philo)
{
	if (philo->n % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->lfork]);
		print_state("has taken left fork", BLUE, philo);
		pthread_mutex_lock(&philo->data->forks[philo->rfork]);
		print_state("has taken right fork", BLUE, philo);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->rfork]);
		print_state("has taken right fork", BLUE, philo);
		pthread_mutex_lock(&philo->data->forks[philo->lfork]);
		print_state("has taken left fork", BLUE, philo);
	}
	if (philo->data->has_died || philo->data->done_eating)
		free_forks(philo);
	else
		eating(philo);
}

void*	dining(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->data->has_died && !philo->data->done_eating)
	{
		if (!philo->data->has_died && !philo->data->done_eating)
			take_forks(philo);
		if (!philo->data->has_died && !philo->data->done_eating)
			sleeping(philo);
	}
	return (NULL);
}