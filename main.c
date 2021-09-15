#include "philo.h"

void	check1(t_philosopher *philosopher)
{
	if((get_time() - philosopher->last_meal) >= philosopher->data->time_to_die)
	{
		philosopher->data->flag_death = 1;
		print_status(philosopher, 1);
		pthread_mutex_lock(&philosopher->data->death);
	}
}

void	check_philo(t_philosopher *philosophers)
{
	int	i;

	while (!philosophers->data->flag_death)
	{
		i = 0;
		while(!philosophers->data->flag_death && i < philosophers->data->number_of_philosophers)
		{
			unsigned long curr_time = get_time();
			// printf("A: %lu B: %lu C: %d\n", curr_time, (&philosophers[i])->last_meal, data->time_to_die);
			// unsigned long last_m = (&philosophers[i])->last_meal;
			// printf("diff: %lu\n", (curr_time - last_m));
			check1(&philosophers[i]);
			// if((get_time() - philosophers[i].last_meal) > (unsigned long)data->time_to_die)
			// {
			// 	data->flag_death = 1;
			// 	pthread_mutex_lock(&philosophers[i].data->death);
			// 	print_status(&philosophers[i], 1);
			// }
			// else if(data->full_philo == data->number_of_philosophers)
			// 	print_status(&philosophers[i], 9);
			i++;
		}
	}
}

void	init_data(t_data *data)
{
// 	data->number_of_philosophers = 0;
// 	data->time_to_die = 0;
// 	data->time_to_eat = 0;
// 	data->time_to_sleep = 0;
// 	data->number_of_times_each_philosopher_must_eat = 0;
// 	pthread_mutex_init(&data->print_message, NULL);
// 	pthread_mutex_init(&data->death, NULL);
	// data->flag_death = 0;
	// data->full_philo = 0;
}

int	init_philosophers(t_data *data, t_philosopher *philosophers)
{
	int	i;

	i = 0;

	data->forks = malloc(sizeof(pthread_mutex_t *) * data->number_of_philosophers);
	if (!data->forks)
		return (1);
	while (i < data->number_of_philosophers)
	{
		data->forks[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!data->forks[i])
			return (1);
		pthread_mutex_init(data->forks[i], NULL);
		i++;
	}
	i = 0;
	data->flag_death = 0;
	data->full_philo = 0;
	while (i < data->number_of_philosophers)
	{
		philosophers[i].id = i + 1;
		philosophers[i].data = data;
		// pthread_mutex_init(&philosophers[i].left_fork, NULL);
		if (philosophers[i].id % 2 == 0)
		{
			philosophers[i].left_fork = data->forks[i];
			philosophers[i].right_fork = data->forks[(i + 1) % data->number_of_philosophers];
		}
		else
		{
			philosophers[i].left_fork = data->forks[(i + 1) % data->number_of_philosophers];
			philosophers[i].right_fork = data->forks[i];
		}
		// if (philosophers[i].id == 1)
		// 	philosophers[i].right_fork = &philosophers[data->number_of_philosophers].left_fork;
		// else
		// 	philosophers[i].right_fork = &philosophers[i - 1].left_fork;
		philosophers[i].times_of_eating = 0;
		i++;
	}
	return (0);
}

int		check_args(char *arg, t_data *data)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]))
			i++;
		else
		{
			printf("Incorrect parameters - parameters can only be positive numbers.\n");
			free(data);
			exit(1);
		}
	}
	return (ft_atoi(arg));
}

void	parse_data(char **argv, t_data *data)
{
	data->number_of_philosophers = check_args(argv[1], data);
	data->time_to_die = check_args(argv[2], data);
	data->time_to_eat = check_args(argv[3], data);
	data->time_to_sleep = check_args(argv[4], data);
	if (argv[5])
		data->number_of_times_each_philosopher_must_eat = check_args(argv[5], data);
	pthread_mutex_init(&data->print_message, NULL);
	pthread_mutex_init(&data->death, NULL);
}

int		main (int argc, char** argv)
{
	t_data			*data;
	t_philosopher	*philosophers;
	pthread_t		*threads;
	int				i;

	if (argc < 5 || argc > 6)
	{
		printf("Incorrect numbers of parameters - the program needs 4 or 5 parameters.\n");
		return (1);
	}
	data = malloc(sizeof(t_data));
	init_data(data);
	parse_data(argv, data);
	philosophers = malloc(sizeof(t_philosopher) * data->number_of_philosophers);
	threads = malloc(sizeof(pthread_t) * data->number_of_philosophers);
	if (!philosophers || !threads)
		return (1);
	if (init_philosophers(data, philosophers))
		printf("Error\n");
	i = 0;
	while (i < data->number_of_philosophers)
	{
		philosophers[i].start_philo = get_time();
		pthread_create(&threads[i], NULL, life_cycle, &philosophers[i]);
		usleep(50);
		i++;
	}
	check_philo(philosophers);
	free_all(data, philosophers, threads);
	return (0);
}
