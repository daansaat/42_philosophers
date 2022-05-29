#include "philo_bonus.h"
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// static void clean_up(t_data *data)
// {
//     sem_post(data->fork_id);
//     sem_post(data->print_id);
//     sem_post(data->meals_id);
//     sem_post(data->done_eating_id);
//     sem_post(data->death_id);
//     sem_post(data->stop_id);
//     sem_close(data->fork_id);
//     sem_close(data->print_id);
//     sem_close(data->meals_id);
//     sem_close(data->done_eating_id);
//     sem_close(data->death_id);
//     sem_close(data->stop_id);
//     free(data.pid_child);
// }

static int	ft_input_help(void)
{
	printf(" ____________________________________________________ \n");
	printf("|                                                    |\n");
	printf("|          Please enter 4 or 5 VALID arguments       |\n");
	printf("|____________________________________________________|\n");
	printf("|                                                    |\n");
	printf("|         [1][%sNumber of philosophers%s][2 - 2000]      |\n", PURPLE, RESET);
	printf("|         [2][%sTime to die%s][milliseconds]             |\n", RED, RESET);
	printf("|         [3][%sTime to eat%s][milliseconds]             |\n", GREEN, RESET);
	printf("|         [4][%sTime to sleep%s][milliseconds]           |\n", YELLOW, RESET);
	printf("|      (( [5][%sNumber of meals%s][ > 1] ))              |\n", TEAL, RESET);
	printf("|____________________________________________________|\n");
	printf("\n");
	return (1);
}

void kill_children(t_data *data)
{
    int i;

    i = 0;
    while (data->pid_child[i])
    {
        if (kill(data->pid_child[i], SIGKILL) != 0)
            ft_error(data, "kill() failed");
        i++;
    }
    printf("%s", RESET);
}

int main(int argc, char **argv)
{
    t_data  data;

	if (argc < 5 || argc > 6)
		return (ft_input_help());
	if (!ft_is_digit(argv))
		return (ft_input_help());    
    if (ft_atoi(argv[1]) < 2 || ft_atoi(argv[1]) > 2000)
		return (ft_input_help());
	if (argv[5] && ft_atoi(argv[5]) <= 0)
			return (0);
    init_struct(&data, argv);
    init_semaphore(&data);
    init_processes(&data);
    kill_children(&data);
    // clean_up(&data);
    return (0);
}