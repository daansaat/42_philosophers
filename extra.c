// void*	sleeping(void *arg)
// {
// 	pthread_mutex_lock(arg);
// 	printf("P1 is sleeping\n");
// 	usleep(3000000);
// 	pthread_mutex_unlock(arg);
// 	return (0);
// }

// void*	thinking(void *arg)
// {
// 	pthread_mutex_lock(arg);
// 	printf("P1 is thinking\n");
// 	usleep(3000000);
// 	pthread_mutex_unlock(arg);
// 	return (0);
// }

// void*	dying(void *arg)
// {
// 	pthread_mutex_lock(arg);
// 	printf("P1 is eating\n");
// 	usleep(3000000);
// 	pthread_mutex_unlock(arg);
// 	return (0);
// }

// void	init_struct(char **argv, t_data *data)
// {

// }