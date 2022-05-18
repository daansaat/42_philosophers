#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

static void	meals_monitor(t_data * data)
{
	int	i;

	i = 0;
	while (data->philo[i].meals == 0)
	{
		i++;
		if (i == data->p)
			data->done_eating = 1;
	}
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
				data->has_died = 1;
				print_state("has died", RED, &data->philo[i]);
				return ;
			}
			i++;
		}
		meals_monitor(data);
		i = 0;
	}
}