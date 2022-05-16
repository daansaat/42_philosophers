#include "philo.h"
#include <stdio.h>
#include <unistd.h>

void*	take_forks(void *arg)
{
	t_philo			*philo;

	philo = arg;
	print_state("is thinking", PURPLE, philo);
	if (philo->nbr_left_fork < philo->nbr_right_fork)
	{
		pthread_mutex_lock(philo->left_fork);
		print_state("has taken left fork", BLUE, philo);
		pthread_mutex_lock(philo->right_fork);
		print_state("has taken right fork", BLUE, philo);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_state("has taken right fork", BLUE, philo);
		pthread_mutex_lock(philo->left_fork);
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
	if (philo->meals)
		philo->meals -= 1;
	usleep(philo->data->time_eat * 1000);
	return (0);
}

void*	sleeping(void *arg)
{
	t_philo			*philo;
	
	philo = arg;
	print_state("is sleeping", YELLOW, philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	usleep(philo->data->time_sleep * 1000);
	return (0);
}

void*	dining(void *arg)
{
	t_philo			*philo;

	philo = arg;
	while (!philo->data->has_died)
	{
		if (!philo->data->has_died)
			take_forks(philo);
		if (!philo->data->has_died)
			eating(philo);
		printf("%d\n", philo->meals);
		// if (philo->meals <= 0)
		// 	break ;
		if (!philo->data->has_died)
			sleeping(philo);
	}
	return (0);
}