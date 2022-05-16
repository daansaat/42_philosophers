#include "philo.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_data			data;
	pthread_t		*threads;
	int				i;

	(void)argc;
	init_struct(argv, &data);
	threads = malloc(sizeof(pthread_t) * atoi(argv[1]));
	i = 0;
	while (i < data.p)
	{
		pthread_create(&threads[i], NULL, &dining, (void*)&data.philo[i]);
		i++;
	}
	i = 0;
	death_monitor(&data);
	while (i < data.p)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	return (0);
}