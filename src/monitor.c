#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

void*	meals_monitor(void *arg)
{
	t_data	*data;
	int	i;

	data = arg;
	i = 0;
	while (data->philo[i].meals == 0)
	{
		i++;
		if (i == data->p)
			data->done_eating = 1;
	}
	return (0);
}

void	death_monitor(t_data *data)
{
	int		i;
	long	time;

	i = 0;
	while (!data->done_eating)
	{
		while (i < data->p)
		{
			time = ft_time();
			if (time - data->philo[i].time_last_meal > data->time_die \
			&& data->philo[i].meals != 0)
			{
				print_state("has died", RED, &data->philo[i]);
				data->has_died = 1;
				return ;
			}
			i++;
		}
		// meals_monitor(data);
		i = 0;
	}
}