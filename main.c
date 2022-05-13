#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "philo.h"

void red() {
  printf("\033[1;31m");
}
void yellow() {
  printf("\033[1;33m");
}
void green () {
	printf("\033[0;32m");
}
void purple () {
	printf("\033[0;35m");
}
void blue () {
  printf("\033[0;34m");
}
void reset () {
  printf("\033[0m");
}
void*	eating(void *arg)
{
	t_philo	*philo;

	philo = arg;
	pthread_mutex_lock(philo->left_fork);
	blue();
	// printf("P%d has taken left fork\n", philo->n + 1);
	pthread_mutex_lock(philo->right_fork);
	purple();
	// printf("P%d has taken right fork\n", philo->n + 1);
	green();
	printf("P%d is eating\n", philo->n + 1);
	usleep(5000000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	yellow();
	printf("P%d is sleeping\n", philo->n + 1);
	reset();
	return (0);
}

void	init_struct(char **argv, t_data *data)
{
	int	i;

	data->p = atoi(argv[1]);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->p);
	data->philo = malloc(sizeof(t_philo) * data->p);
	i = 0;
	while (i++ < data->p)
		pthread_mutex_init(&data->forks[i], NULL);
	i = 0;
	while (i < data->p)
	{
		data->philo[i].n = i;
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].right_fork = &data->forks[(i + 1) % data->p];
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
		pthread_create(&threads[i], NULL, &eating, (void*)&data.philo[i]);
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