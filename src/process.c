#include "philo.h"
#include <stdio.h>
#include <unistd.h>

static void	free_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->lfork]);
	pthread_mutex_unlock(&philo->data->forks[philo->rfork]);
}

static void	take_forks(t_philo *philo)
{
	print_state("is thinking", PURPLE, philo);
	if (philo->lfork < philo->rfork)
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
}

static void	eating(t_philo *philo)
{
	philo->time_last_meal = ft_time();
	if (philo->meals > 0)
		philo->meals -= 1;
	print_state("is eating", GREEN, philo);
	usleep(philo->data->time_eat * 1000);
	pthread_mutex_unlock(&philo->data->forks[philo->lfork]);
	pthread_mutex_unlock(&philo->data->forks[philo->rfork]);
}

static void	sleeping(t_philo *philo)
{
	print_state("is sleeping", YELLOW, philo);
	usleep(philo->data->time_sleep * 1000);
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
			eating(philo);
		if (!philo->data->has_died && !philo->data->done_eating)
			sleeping(philo);
	}
	return (NULL);
}