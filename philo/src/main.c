/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:22:37 by dsaat         #+#    #+#                 */
/*   Updated: 2022/06/03 09:12:04 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

static int	ft_input_help(void)
{
	printf(" ____________________________________________________ \n");
	printf("|                                                    |\n");
	printf("|          Please enter 4 or 5 VALID arguments       |\n");
	printf("|____________________________________________________|\n");
	printf("|                                                    |\n");
	printf("|         [1][%sNumber of philosophers%s][2 - 2000]      |\n", \
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

static void	free_and_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->p)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->meals_monitor);
	free(data->threads);
	free(data->forks);
	free(data->philo);
}

int	main(int argc, char **argv)
{
	t_data			data;

	if (argc < 5 || argc > 6)
		return (ft_input_help());
	if (!ft_is_digit(argv))
		return (ft_input_help());
	if (ft_atoi(argv[1]) < 2 || ft_atoi(argv[1]) > 2000)
		return (ft_input_help());
	if (argv[5] && ft_atoi(argv[5]) <= 0)
		return (ft_input_help());
	if (init_struct(argv, &data))
		return (1);
	if (init_mutex(&data))
		return (1);
	if (init_monitor(&data) || init_threads(&data))
		return (1);
	free_and_destroy(&data);
	return (0);
}
