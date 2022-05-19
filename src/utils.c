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

	pthread_mutex_lock(&philo->data->print);
	if (!philo->data->has_died && !philo->data->done_eating)
	{
		timestamp = ft_time() - philo->data->time_start;
		printf("%ldms %sP%d %s\n%s", timestamp, color, philo->n + 1, str, RESET);
	}
	pthread_mutex_unlock(&philo->data->print);
}

int	ft_atoi(const char *str)
{
	unsigned long int	x;
	unsigned long int	i;
	unsigned long int	sign;

	x = 0;
	i = 0;
	sign = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		x = x * 10 + str[i] - '0';
		i++;
	}
	return (x * sign);
}
