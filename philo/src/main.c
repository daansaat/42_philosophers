/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:22:37 by dsaat         #+#    #+#                 */
/*   Updated: 2022/06/11 10:56:17 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_data			data;

	if (argc < 5 || argc > 6)
		return (ft_input_help());
	if (!ft_is_digit(argv))
		return (ft_input_help());
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 2000
		|| ft_atoi(argv[2]) < 1 || ft_atoi(argv[3]) < 1
		|| ft_atoi(argv[4]) < 1)
		return (ft_input_help());
	if (argv[5] && ft_atoi(argv[5]) <= 0)
		return (ft_input_help());
	if (init_struct(argv, &data))
		return (1);
	if (init_mutex(&data))
		return (1);
	if (init_threads(&data))
		return (1);
	return (0);
}
