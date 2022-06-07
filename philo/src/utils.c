/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:22:49 by dsaat         #+#    #+#                 */
/*   Updated: 2022/06/07 12:27:51 by dsaat         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <stdio.h>

int	ft_error(char *str)
{
	printf("%s\n", str);
	return (1);
}

long	ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}	

void	print_state(char *str, char *color, t_philo *philo)
{
	long	time_ms;

	pthread_mutex_lock(&philo->data->print);
	if (!philo->data->has_died && !philo->data->done_eating)
	{
		time_ms = ft_time() - philo->data->time_start;
		printf("%ldms %sP%d %s\n%s", time_ms, color, philo->n + 1, str, RESET);
		philo->time_print = ft_time();
	}
	pthread_mutex_unlock(&philo->data->print);
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
