#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

void	death_monitor(t_data *data)
{
	int		i;
	long	time;

	i = 0;
	while (1)
	{
		while (i < data->p)
		{
			time = ft_time();
			if (time - data->philo[i].time_last_meal > data->time_die \
			&& data->philo[i].meals != 0)
			{
				data->has_died = 1;
				print_state("has died", RED, &data->philo[i]);
				printf("%d\n", data->philo[i].meals);
				return;
			}
			i++;
		}
		i = 0;
	}
}