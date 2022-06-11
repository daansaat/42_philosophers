/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_bonus.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:23:03 by dsaat         #+#    #+#                 */
/*   Updated: 2022/06/11 14:33:59 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (ft_input_help());
	if (!ft_is_digit(argv))
		return (ft_input_help());
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 500)
		return (ft_input_help());
	if (argv[5] && ft_atoi(argv[5]) <= 0)
		return (ft_input_help());
	init_struct(&data, argv);
	init_semaphore(&data);
	init_processes(&data);
	return (0);
}
