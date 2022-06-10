/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:22:37 by dsaat         #+#    #+#                 */
/*   Updated: 2022/06/10 10:01:40 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static void	free_and_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->p)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mutex);
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
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 2000)
		return (ft_input_help());
	if (argv[5] && ft_atoi(argv[5]) <= 0)
		return (ft_input_help());
	if (init_struct(argv, &data))
		return (-1);
	if (init_mutex(&data))
		return (-1);
	if (init_threads(&data))
		return (-1);
	free_and_destroy(&data);
	return (0);
}
