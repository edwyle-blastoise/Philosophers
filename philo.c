#include "philo.h"

void	print_status(t_philosopher *philosopher, int status)
{
	pthread_mutex_lock(&philosopher->data->print_message);
	if (status == 1)
		printf("%lu %d died\n", get_time() - philosopher->start_philo, philosopher->id);
	else if (status == 2)
	{
		printf("%lu %d took the left fork\n", get_time() - philosopher->start_philo, philosopher->id);
	}
	else if (status == 3)
		printf("%lu %d took the right fork\n", get_time() - philosopher->start_philo, philosopher->id);
	else if (status == 4)
		printf("%lu %d is eating\n", get_time() - philosopher->start_philo, philosopher->id);
	else if (status == 5)
		printf("%lu %d is sleeping\n", get_time() - philosopher->start_philo, philosopher->id);
	else if (status == 6)
		printf("%lu %d is thinking\n", get_time() - philosopher->start_philo, philosopher->id);
	else if (status == 7)
		printf("%lu %d put down the right fork\n", get_time() - philosopher->start_philo, philosopher->id);
	else if (status == 8)
		printf("%lu %d put down the left fork\n", get_time() - philosopher->start_philo, philosopher->id);
	else if (status == 9)
		printf("Each pholosopher ate %d times\n", philosopher->data->number_of_times_each_philosopher_must_eat);
	pthread_mutex_unlock(&philosopher->data->print_message);

}

void	philo_doings(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->left_fork);
	print_status(philosopher, 2);
	pthread_mutex_lock(philosopher->right_fork);
	print_status(philosopher, 3);

	philosopher->last_meal = get_time();

	print_status(philosopher, 4);
	ft_usleep(philosopher->data->time_to_eat);

	philosopher->times_of_eating++;
	if (philosopher->times_of_eating == philosopher->data->number_of_times_each_philosopher_must_eat)
	{
		philosopher->data->full_philo++;
		if (philosopher->data->full_philo == philosopher->data->number_of_philosophers)
		{
			pthread_mutex_lock(&philosopher->data->death);
			// print_status(philosopher, 9);
			philosopher->data->flag_death = 1;
		}
	}
	pthread_mutex_unlock(philosopher->right_fork);
	print_status(philosopher, 7);
	pthread_mutex_unlock(&philosopher->left_fork);
	print_status(philosopher, 8);

	print_status(philosopher, 5);
	ft_usleep((philosopher->data->time_to_sleep));
	print_status(philosopher, 6);
}

void*	life_cycle(void *philo)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher*)philo;
	philosopher->last_meal = get_time();
	if (philosopher->data->number_of_philosophers > 1)
		if (philosopher->id % 2 == 0)
			usleep(100);
	while (1)
	{
		philo_doings(philosopher);
	}

	return (NULL);
}
