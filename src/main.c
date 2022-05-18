#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_data			data;
	

	(void)argc;
	init_struct(argv, &data);
	init_mutex(&data);
	init_threads(&data);
	return (0);
}