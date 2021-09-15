#include "philo.h"

// void	philoPrint(t_philosopher *philo, const char *msg)
// {
// 	pthread_mutex_lock(&philo->data->print_message);
// 	printf("%lu Philo %d %s\n", (get_time() - philo->start_philo), \
// 			philo->id, msg);
// 	pthread_mutex_unlock(&philo->data->print_message);
// }
// ----

void	print_status(t_philosopher *philosopher, int status)
{
	pthread_mutex_lock(&philosopher->data->print_message);
	if (status == 1)
		printf("%llu %d died\n", get_time() - philosopher->start_philo, philosopher->id);
	else if (status == 2)
	{
		printf("%llu %d take the left fork\n", get_time() - philosopher->start_philo, philosopher->id);
	}
	else if (status == 3)
		printf("%llu %d take the right fork\n", get_time() - philosopher->start_philo, philosopher->id);
	else if (status == 4)
		printf("%llu %d is eating\n", get_time() - philosopher->start_philo, philosopher->id);
	else if (status == 5)
		printf("%llu %d is sleeping\n", get_time() - philosopher->start_philo, philosopher->id);
	else if (status == 6)
		printf("%llu %d is thinking\n", get_time() - philosopher->start_philo, philosopher->id);
	else if (status == 7)
		printf("%llu %d put down the right fork\n", get_time() - philosopher->start_philo, philosopher->id);
	else if (status == 8)
		printf("%llu %d put down the left fork\n", get_time() - philosopher->start_philo, philosopher->id);
	else if (status == 9)
		printf("Each pholosopher ate %d times\n", philosopher->data->number_of_times_each_philosopher_must_eat);
	pthread_mutex_unlock(&philosopher->data->print_message);
}

void	philo_doings(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->left_fork);
	print_status(philosopher, 2);
	pthread_mutex_lock(philosopher->right_fork);
	print_status(philosopher, 3);

	print_status(philosopher, 4);
	philosopher->last_meal = get_time();
	// printf("last_meal: %lu\n", last_meal);

	philosopher->times_of_eating++;
	if (philosopher->times_of_eating == philosopher->data->number_of_times_each_philosopher_must_eat)
	{
		philosopher->data->full_philo++;
		if (philosopher->data->full_philo == philosopher->data->number_of_philosophers)
		{
			philosopher->data->flag_death = 1;
			print_status(philosopher, 9);
			pthread_mutex_lock(&philosopher->data->death);
		}
	}
	ft_usleep(philosopher->data->time_to_eat);
	pthread_mutex_unlock(philosopher->right_fork);
	print_status(philosopher, 7);
	pthread_mutex_unlock(philosopher->left_fork);
	print_status(philosopher, 8);

	print_status(philosopher, 5);
	ft_usleep(philosopher->data->time_to_sleep);
	print_status(philosopher, 6);
}

// void	eat(t_philosopher *philo)
// {
// 	pthread_mutex_lock(philo->left_fork);
// 	philoPrint(philo, "take first fork");

// 	pthread_mutex_lock(philo->right_fork);
// 	philoPrint(philo, "take second fork");

// 	philoPrint(philo, "is eating");
// 	philo->last_meal = get_time();
// 	ft_usleep(philo->data->time_to_eat);
// 	pthread_mutex_unlock(philo->left_fork);
// 	pthread_mutex_unlock(philo->right_fork);
// }

void*	life_cycle(void *philo)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher*)philo;
	philosopher->last_meal = get_time();
	// if (philosopher->data->number_of_philosophers > 1)
	// 	if (philosopher->id % 2 == 0)
	// 		usleep(100);
	while (1)
	{
		philo_doings(philosopher);
		// eat(philosopher);
		// philoPrint(philosopher, "is sleeping");
		// ft_usleep(philosopher->data->time_to_sleep);
		// philoPrint(philosopher, "is thinking");

	}
	return (NULL);
}
