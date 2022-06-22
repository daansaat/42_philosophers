/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_bonus.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:23:09 by dsaat         #+#    #+#                 */
/*   Updated: 2022/06/22 13:19:23 by dsaat         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdio.h>
#include <sys/time.h>

void	ft_error(t_data *data, char *str)
{
	printf("%s%s%s\n", RED, str, RESET);
	ft_stop(data);
}

long	ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}	

int	ft_input_help(void)
{
	printf(" ____________________________________________________ \n");
	printf("|                                                    |\n");
	printf("|          Please enter 4 or 5 VALID arguments       |\n");
	printf("|____________________________________________________|\n");
	printf("|                                                    |\n");
	printf("|         [1][%sNumber of philosophers%s][2 - 500]       |\n", \
	PURPLE, RESET);
	printf("|         [2][%sTime to die%s][milliseconds]             |\n", \
	RED, RESET);
	printf("|         [3][%sTime to eat%s][milliseconds]             |\n", \
	GREEN, RESET);
	printf("|         [4][%sTime to sleep%s][milliseconds]           |\n", \
	YELLOW, RESET);
	printf("|      (( [5][%sNumber of meals%s][ > 0] ))              |\n", \
	TEAL, RESET);
	printf("|____________________________________________________|\n");
	printf("\n");
	return (1);
}

long	ft_atol(const char *str, long max)
{
	long	nb;

	nb = 0;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (-1);
		nb = nb * 10 + (*str - '0');
		str++;
		if (nb > max)
			return (-1);
	}
	return (nb);
}
