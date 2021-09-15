#include "philo.h"


unsigned long	get_time(void)
{
	struct timeval	current_time;
	unsigned long	sec;
	unsigned long	msec;

	gettimeofday(&current_time, NULL);
	sec = current_time.tv_sec * 1000;
	msec = current_time.tv_usec / 1000;
	return (sec + msec);
}

int	ft_atoi(char *str)
{
	int i;
	int result;
	int sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}


void	ft_usleep(useconds_t time)
{
	unsigned long start;

	start = get_time();
	while (get_time() - start < time)
		usleep(50);
}

int	destroy_mutex_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(data->forks[i]);
		free(data->forks[i]);
		i++;
	}
	return (0);
}

void	free_all(t_data *data, t_philosopher	*philosophers, pthread_t *threads)
{
	// int	i;

	// i = 0;
	// while (i < data.number_of_philosophers)
	// {
	// 	pthread_detach(threads[i]);
	// 	i++;
	// }
	// pthread_mutex_destroy(philosophers->left_fork);
	// pthread_mutex_destroy(philosophers->right_fork);
	destroy_mutex_forks(data);
	pthread_mutex_destroy(&data->print_message);
	pthread_mutex_destroy(&data->death);
	free(data->forks);
	free(philosophers);
	free(threads);
}