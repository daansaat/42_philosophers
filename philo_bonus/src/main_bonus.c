/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_bonus.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:23:03 by dsaat         #+#    #+#                 */
/*   Updated: 2022/06/11 22:21:44 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <limits.h>

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (ft_input_help());
	data.p = ft_atol(argv[1], INT_MAX);
	data.meals = -1;
	data.time_die = ft_atol(argv[2], LONG_MAX / 1000);
	data.time_eat = ft_atol(argv[3], LONG_MAX / 1000);
	data.time_sleep = ft_atol(argv[4], LONG_MAX / 1000);
	if (argv[5])
		data.meals = ft_atol(argv[5], INT_MAX);
	if (data.p < 1 || data.p > 500 || data.time_die < 1 
		|| data.time_eat < 1 || data.time_sleep < 1)
		return (ft_input_help());
	if (argv[5] && data.meals < 1)
		return (ft_input_help());
	init_semaphore(&data);
	init_processes(&data);
	return (0);
}
