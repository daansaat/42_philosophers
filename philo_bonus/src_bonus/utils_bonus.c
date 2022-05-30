#include "philo_bonus.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

void	ft_error(char *str)
{
    printf("%s%s%s\n", RED, str, RESET);
	exit(EXIT_FAILURE);
}

long	ft_time(void)
{
	struct timeval	time;
	
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}	

void	print_state(char *str, char *color, t_data *data)
{
	long	time_ms;

	ft_check(sem_wait(data->print_id));
	time_ms = ft_time() - data->time_start;
	printf("%s%ldms %sP%d %s\n%s", RESET, time_ms, color, data->n + 1, str, RESET);
	ft_check(sem_post(data->print_id));
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
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		x = x * 10 + str[i] - '0';
		i++;
	}
	return (x * sign);
}

int	ft_is_digit(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
