#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

void*	meals_monitor(void *arg)
{
	t_data	*data;
	int	i;

	data = arg;
	i = 0;
	while (i < data->p)
	{
		pthread_mutex_lock(&data->print);
		while (data->philo[i].meals == 0)
		{
			i++;
			if (i == data->p)
			{
				data->done_eating = 1;
				// pthread_mutex_unlock(&data->print);
				break ;
				printf("done\n");
			}
		}
		pthread_mutex_unlock(&data->print);
		if (data->done_eating == 1)
		{
			printf("here ok\n");
			return (0);
		}
		i = 0;
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
				pthread_mutex_lock(&data->print);
				printf("has died\n");
				// print_state("has died", RED, &data->philo[i]);
				data->has_died = 1;
				pthread_mutex_unlock(&data->print);
				return ;
			}
			i++;
		}
		// meals_monitor(data);
		i = 0;
	}
}