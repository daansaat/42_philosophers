#include "philo.h"
#include <stdio.h>
#include <unistd.h>

void*	take_forks(void *arg)
{
	t_philo			*philo;

	philo = arg;
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
	return (0);
}

void*	eating(void *arg)
{
	t_philo			*philo;

	philo = arg;
	philo->time_last_meal = ft_time();
	print_state("is eating", GREEN, philo);
	if (philo->meals > 0)
		philo->meals -= 1;
	usleep(philo->data->time_eat * 1000);
	return (0);
}

void*	sleeping(void *arg)
{
	t_philo			*philo;
	
	philo = arg;
	print_state("is sleeping", YELLOW, philo);
	pthread_mutex_unlock(&philo->data->forks[philo->lfork]);
	pthread_mutex_unlock(&philo->data->forks[philo->rfork]);
	usleep(philo->data->time_sleep * 1000);
	return (0);
}

void*	dining(void *arg)
{
	t_philo			*philo;

	philo = arg;
	while (!philo->data->has_died)// && philo->meals != 0)
	{
		if (!philo->data->has_died)// && philo->meals != 0)
			take_forks(philo);
		// break ;
		if (!philo->data->has_died)// && philo->meals != 0)
			eating(philo);
		// if (philo->meals == 0)
		// 	return (0);
		if (!philo->data->has_died)// && philo->meals != 0)
			sleeping(philo);
	}
	return (0);
}