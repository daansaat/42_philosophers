#include "philo.h"
#include <sys/time.h>
#include <stdio.h>

long	ft_time(void)
{
	struct timeval	time;
	
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}	

void	print_state(char *str, char *color, t_philo *philo)
{
	long	timestamp;

	if (!philo->data->has_died && !philo->data->done_eating)
	{
		pthread_mutex_lock(&philo->data->print);
		timestamp = ft_time() - philo->data->time_start;
		printf("%ldms %sP%d %s\n%s", timestamp, color, philo->n + 1, str, RESET);
		pthread_mutex_unlock(&philo->data->print);
	}
}