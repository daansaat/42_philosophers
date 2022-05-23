#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

// static void	free_and_destroy(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->p)
// 	{
// 		pthread_mutex_destroy(&data->forks[i]);
// 		i++;
// 	}
// 	pthread_mutex_destroy(&data->print);
// 	free(data->forks);
// 	free(data->philo);
// }

int	main(int argc, char **argv)
{
	t_data			data;

	(void)argc;
	if (init_struct(argv, &data))
		return (0);
	init_philo(argv, &data);
	init_mutex(&data);
	if (init_threads(&data))
		return (0);
	// free_and_destroy(&data);
	return (0);
}