/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_bonus.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsaat <dsaat@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:23:03 by dsaat         #+#    #+#                 */
/*   Updated: 2022/06/03 07:59:17 by daansaat      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void	clean_up(t_data *data)
{
	kill_children(data);
	sem_unlink("/fork");
	sem_unlink("/can_sit");
	sem_unlink("/print");
	sem_unlink("/meals");
	sem_unlink("/done_eating");
	sem_unlink("/death");
	sem_close(data->fork_id);
	sem_close(data->can_sit_id);
	sem_close(data->print_id);
	sem_close(data->done_eating_id);
	free(data->pid_child);
}

static int	ft_input_help(void)
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

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (ft_input_help());
	if (!ft_is_digit(argv))
		return (ft_input_help());
	if (ft_atoi(argv[1]) < 2 || ft_atoi(argv[1]) > 500)
		return (ft_input_help());
	if (argv[5] && ft_atoi(argv[5]) <= 0)
		return (ft_input_help());
	init_struct(&data, argv);
	init_semaphore(&data);
	init_processes(&data);
	while (waitpid(0, NULL, 0) > 0);
	clean_up(&data);
	return (0);
}
