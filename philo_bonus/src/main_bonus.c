/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_bonus.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:23:03 by dsaat         #+#    #+#                 */
/*   Updated: 2022/06/10 11:46:38 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdlib.h>
#include <stdio.h>

void	clean_up(t_data *data)
{
	sem_unlink("/fork");
	sem_unlink("/can_sit");
	sem_unlink("/mutex");
	sem_unlink("/done_eating");
	sem_unlink("/death");
	sem_close(data->fork_id);
	sem_close(data->can_sit_id);
	sem_close(data->mutex_id);
}

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
	while (waitpid(0, NULL, 0) > 0)
		;
	clean_up(&data);
	return (0);
}
