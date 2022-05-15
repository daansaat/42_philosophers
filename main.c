#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void*	take_forks(void *arg)
{
	t_philo	*philo;

	philo = arg;
	printf("%sP%d is thinking\n%s", PURPLE, philo->n + 1, RESET);
	if (philo->nbr_left_fork < philo->nbr_right_fork)
	{
		pthread_mutex_lock(philo->left_fork);
		printf("%sP%d has taken left fork\n%s", BLUE, philo->n + 1, RESET);
		pthread_mutex_lock(philo->right_fork);
		printf("%sP%d has taken right fork\n%s", BLUE, philo->n + 1, RESET);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		printf("%sP%d has taken right fork\n%s", BLUE, philo->n + 1, RESET);
		pthread_mutex_lock(philo->left_fork);
		printf("%sP%d has taken left fork\n%s", BLUE, philo->n + 1, RESET);
	}
	eat(philo);
	return (0);
}

void*	eat(void *arg)
{
	t_philo	*philo;

	philo = arg;
	printf("%sP%d is eating\n%s", GREEN, philo->n + 1, RESET);
	usleep(2000000);
	sleeping(philo);
	return (0);
}

void*	sleeping(void *arg)
{
	t_philo	*philo;
	
	philo = arg;
	printf("%sP%d is sleeping\n%s", YELLOW, philo->n + 1, RESET);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	usleep(1000000);
	take_forks(philo);
	return (0);
}

void	init_struct(char **argv, t_data *data)
{
	int	i;

	data->p = atoi(argv[1]);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->p);
	data->philo = malloc(sizeof(t_philo) * data->p);
	i = 0;
	while (i < data->p)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->p)
	{
		data->philo[i].n = i;
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].nbr_left_fork = i;
		data->philo[i].right_fork = &data->forks[(i + 1) % data->p];
		data->philo[i].nbr_right_fork = (i + 1) % data->p;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data			data;
	pthread_t		*threads;
	int				i;

	(void)argc;
	init_struct(argv, &data);
	threads = malloc(sizeof(pthread_t) * atoi(argv[1]));
	i = 0;
	i = 0;
	while (i < data.p)
	{
		pthread_create(&threads[i], NULL, &take_forks, (void*)&data.philo[i]);
		// pthread_join(threads[i], NULL);
		i++;
	}
	i = 0;
	while (i < data.p)
	{
		// pthread_create(&threads[i], NULL, &eating, (void*)&data.philo[i]);
		pthread_join(threads[i], NULL);
		i++;
	}
	// pthread_join(P[i], NULL);
	// printf("%d\n", i);
	// pthread_create(&P[i], NULL, &sleeping, &mutex[i]);
	// pthread_create(&P[i], NULL, &thinking, &mutex[i]);
	// while (1);
	return (0);
}